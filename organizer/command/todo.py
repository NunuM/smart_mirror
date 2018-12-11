#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sqlite3
import json
import configparser
import getopt
import sys
import os.path
from datetime import datetime
import pytz


def usage():
    print("""\033[1mUSAGE:\033[0m organize [OPTIONS]... [TITLE]...

        Organizer let's you create little notes that you can set
        up and be notified.

        You can set the recipients that will be notified:
        $ snap set organizer recipients="your-email,...,.."
        
        You can change the date format that you pass with argument -a:
        $ snap set organizer indateformate="%%Y-%%m-%%d %%H:%%M"
        
        You can also change the output format of date:
        $ snap set organizer outateformate="%%Y-%%m-%%d %%H:%%M"

        To see your snap configuration, you can query:
        $ snap get organizer recipients

    \033[1mOPTIONS:\033[0m
        -c, --create        create new entry.
        -r, --read          search for a existing entry.
        -u, --update        update existing entry.
        -d, --delete        delete existing entry.
        -f, --future        list future entries.
        -o, --old           list old entries.
        -a, --alarm         specify the date.
        -j, --json          print as json.
        -g, --config        set this configuration.
        -h, --help          print this message and exits.

    \033[1mEXAMPLES:\033[0m
        Create multiples notes.
        $ organizer -c "Buy a new moon" "Work meeting"

        Create a note, but I want to be notified, note that the date must 
        be greater than current time, otherwise cannot send int past
        notifications
        $ organizer -a "2018-12-12 10:22" -c "Buy a new moon"
        
        Update older Note. You can also pass the new date with -a argument
        $organizer -u "Old title" "new title" 

        Override current configuration by this configuration:
        $ organizer -g /home/my.cfg 


    \033[1mPROJECT:\033[0m

        		Made with love by nunum
        """)

    return True


def init_database(config):
    """
    Create database connection, and required tables
    :param config:
    :return: sqlite connection
    """

    db_name = config.get('sqlite', 'name')

    user_dir = config.get('sqlite', 'rel_path')
    db_path = os.path.join(user_dir, db_name)

    conn = sqlite3.connect(db_path)

    conn.execute("""CREATE TABLE IF NOT EXISTS todo
                    (title        TEXT     NOT NULL ,
                     alarm        DATETIME NOT NULL,
                     notifiable   BOOLEAN  DEFAULT FALSE,
                     created      DATETIME NOT NULL
                    )""")
    # speed up searches
    conn.execute("CREATE INDEX IF NOT EXISTS idx_title ON todo(title)")
    conn.execute("CREATE INDEX IF NOT EXISTS idx_alarm ON todo(alarm)")

    return conn


def find_all(conn):
    """
    Load all entries
    :param conn:
    :return:
    """
    query = "SELECT * FROM todo ORDER BY alarm DESC"

    cur = conn.execute(query)

    return [dict((cur.description[i][0], value) \
                 for i, value in enumerate(row)) for row in cur.fetchall()]


def create_todo(conn, config, title, alarm=None, is_verbose=True):
    """
    New database entry
    :param conn:
    :param config:
    :param str title:
    :param str alarm:
    :param is_verbose
    :return:
    """
    query = """INSERT INTO todo (title, alarm, notifiable, created) VALUES (?,?,?,?)"""

    try:
        db_date_format = config.get('sqlite', 'dateformat')
        now = datetime.now(tz=pytz.utc)

        if alarm is None:
            now_formatted = now.strftime(db_date_format)
            row = (title, now_formatted, False, now_formatted)
        else:
            alarm_utc = normalize_date(config, alarm)
            if alarm_utc > now:
                row = (title.encode("utf-8"), alarm_utc.strftime(db_date_format), True, now.strftime(db_date_format))
            else:
                row = (title.encode("utf-8"), alarm_utc.strftime(db_date_format), False, now.strftime(db_date_format))

        conn.execute(query, row)
        conn.commit()

        return {'title': row[0], 'alarm': row[1], 'notifiable': row[2], 'created': row[3]}

    except Exception as e:
        if is_verbose:
            print("Not able to store entry due the following error: {}".format(str(e)))
        return {'error': str(e)}


def find_todo_by_title(conn, config, title, alarm=None):
    """
    Find by title
    :param conn:
    :param config:
    :param title:
    :param alarm:
    :return:
    """
    if alarm is None:
        query = """SELECT * FROM todo WHERE title LIKE '%{}%' """.format(title.replace('\'', '´'))
    else:
        query = """SELECT * FROM todo WHERE title LIKE '%{}%' AND alarm='{}' """ \
            .format(title.replace('\'', '´'),
                    normalize_date(config, alarm).strftime(config.get('sqlite', 'dateformat')))

    cur = conn.execute(query)

    return [dict((cur.description[i][0], value) \
                 for i, value in enumerate(row)) for row in cur.fetchall()]


def find_newest_todo(conn):
    """

    :param conn:
    :return:
    """
    now = datetime.now(tz=pytz.utc)

    query = """SELECT * FROM todo WHERE alarm > '{}' ORDER BY alarm DESC""".format(now)
    cur = conn.execute(query)

    return [dict((cur.description[i][0], value) \
                 for i, value in enumerate(row)) for row in cur.fetchall()]


def find_oldest_todo(conn):
    """
    List all entries older than now UTC
    :param conn:
    :return:
    """
    now = datetime.now(tz=pytz.utc)

    query = """SELECT * FROM todo WHERE alarm <= '{}' ORDER BY alarm ASC""".format(now)
    cur = conn.execute(query)

    return [dict((cur.description[i][0], value) \
                 for i, value in enumerate(row)) for row in cur.fetchall()]


def update_todo(conn, config, original_title, new_title, alarm=None, is_verbose=False):
    """
    Update entry
    :param conn:
    :param config:
    :param original_title:
    :param new_title:
    :param alarm:
    :param is_verbose
    :return:
    """

    if alarm is None:
        query = "UPDATE todo set title = '{}' WHERE title='{}'" \
            .format(new_title.replace('\'', '´'),
                    original_title)
    else:

        now = datetime.now(tz=pytz.utc)
        alarm_utc = normalize_date(config, alarm)
        if alarm_utc > now:
            notifiable = True
        else:
            notifiable = False

        query = "UPDATE todo set title = '{}', alarm='{}', notifiable = {} WHERE title='{}'" \
            .format(new_title.replace('\'', '´'),
                    alarm_utc.strftime(config.get('sqlite', 'dateformat')),
                    '1' if notifiable else '0',
                    original_title.replace('\'', '´'))

    try:
        cursor = conn.execute(query)
        conn.commit()

        return {'updated': cursor.rowcount}
    except Exception as e:
        if is_verbose:
            print("Could not update TODO due the following error: {}".format(str(e)))

    return {'updated': 0}


def delete_todo(conn, config, title, alarm=None, is_verbose=False):
    """
    Delete entry
    :param conn:
    :param config:
    :param title:
    :param alarm:
    :param is_verbose:
    :return:
    """

    if alarm is None:
        query = "DELETE FROM todo WHERE title LIKE '{}'".format(title.replace('\'', '´'))
    else:
        query = "DELETE FROM todo WHERE title LIKE '{}' OR alarm='{}'" \
            .format(title.replace('\'', '´'), str(normalize_date(config, alarm)))

    try:
        cursor = conn.execute(query)
        conn.commit()

        return {'deleted': cursor.rowcount}
    except Exception as e:
        if is_verbose:
            print("Could not delete TODO due the following error: {}".format(str(e)))

    return {'deleted': 0}


def normalize_date(config, date):
    """
    Parse input date, interpreted as local timezone and then
    returns it as UTC date.
    :param config:
    :param date:
    :return: UTC date
    """
    timezone = config.get('organizer', 'timezone')
    local = pytz.timezone(timezone)
    naive = datetime.strptime(date, config.get('organizer', 'indateformat'))
    local_dt = local.localize(naive)

    return local_dt.astimezone(tz=pytz.utc)


def date_to_local(config, date):
    """
    Convert date to local time
    :param config:
    :param date:
    :return:
    """
    timezone = config.get('organizer', 'timezone')
    local = pytz.timezone('UTC')
    naive = datetime.strptime(date, config.get('sqlite', 'dateformat'))
    local_dt = local.localize(naive)

    return local_dt.astimezone(tz=pytz.timezone(timezone))


def print_in_json(container):
    """
    Output as JSON format
    :param container:
    :return:
    """
    print(json.dumps(container))
    return True


def pretty_print(container, config):
    """
    Column entry print
    :param container:
    :return:
    """
    date_format = config.get('organizer', 'outdateformat')

    for todo in container:
        print('-' * 100)
        for key in sorted(todo):
            if key == 'alarm' or key == 'created':
                try:
                    formatted_date = date_to_local(config, todo[key]).strftime(date_format)
                    print("{0:15}| {1:<25}".format((key[0].upper() + key[1:]), formatted_date))
                except ValueError as e:
                    pass
            else:
                print("{0:15}| {1:<25}".format((key[0].upper() + key[1:]),
                                               str(todo[key]).encode('ascii', 'replace').decode()))
        print('-' * 100)
    print("")

    return True


def paginate(todos, config):
    """
    Paginate entries
    :param todos:
    :param config:
    :return:
    """
    current = 0
    num_todos = len(todos)

    for todo in todos:

        pretty_print([todo], config)
        current += 1
        char = input("{} in total of {}. Press enter to continue or q to exit $".format(current, num_todos))
        if char == "q":
            break
        os.system('cls' if os.name == 'nt' else 'clear')

    return True


def main():
    try:
        try:
            opts, args = getopt.getopt(sys.argv[1:], "crudfoa:g:jh",
                                       ["create",
                                        "read",
                                        "update",
                                        "delete",
                                        "future",
                                        "old",
                                        "alarm=",
                                        "json",
                                        "config="
                                        "help"])
        except getopt.GetoptError as err:
            print(str(err))
            sys.exit(0)

        is_to_create = False
        is_to_read = False
        is_to_update = False
        is_to_delete = False
        is_to_display_newest = False
        is_to_display_older = False
        defined_alarm = None
        is_to_print_json = False
        is_verbose = True

        config_filename = "../config.cfg"  # os.path.join(os.environ['SNAP_DATA'], "config.cfg")

        for o, a in opts:
            if o in ("-h", "--help"):
                usage()
                sys.exit(0)
            elif o in ("-c", "--create"):
                is_to_create = True
            elif o in ("-r", "--read"):
                is_to_read = True
            elif o in ("-u", "--update"):
                is_to_update = True
            elif o in ("-d", "--delete"):
                is_to_delete = True
            elif o in ("-f", "--future"):
                is_to_display_newest = True
            elif o in ("-o", "--old"):
                is_to_display_older = True
            elif o in ("-a", "--alarm"):
                defined_alarm = a
            elif o in ("-j", "--json"):
                is_to_print_json = True
                is_verbose = False
            elif o in ("-g", "--config"):
                if os.path.exists(a):
                    config_filename = a
                else:
                    print("Configuration file {} not found, using the default".format(a))
            else:
                print("Option {} is unknown".format(o))

        config = config = configparser.ConfigParser(os.environ)

        try:
            config.read(config_filename)
        except configparser.ParsingError as e:
            error_string = "Could not parse config file {}".format(config_filename)
            print(error_string + str(e))
            sys.exit(1)

        try:
            db_connection = init_database(config)
        except Exception as e:
            print("Could not connect to database, reason:" + str(e))
            sys.exit(1)

        if is_to_create:
            created_todo = []
            for title in args:
                created_todo.append(create_todo(db_connection, config, title, defined_alarm, is_verbose))

            if is_to_print_json:
                print_in_json(created_todo)
            else:
                pretty_print(created_todo, config)

        elif is_to_read:
            matched_todo = []
            for title in args:
                matched_todo = find_todo_by_title(db_connection, config, title, defined_alarm)

            if is_to_print_json:
                print_in_json(matched_todo)
            else:
                pretty_print(matched_todo, config)
        elif is_to_update:
            if len(args) == 2:
                if is_verbose:
                    to_update = find_todo_by_title(db_connection, config, args[0])
                    pretty_print(to_update, config)
                    consent = input('You confirm update y/n?')
                    if consent == 'y':
                        response = update_todo(db_connection, config, args[0], args[1], defined_alarm, True)
                        pretty_print([response], config)
                else:
                    response = update_todo(db_connection, config, args[0], args[1], defined_alarm)
                    print_in_json([response])
            else:
                print ("To update todo two arguments must be provided")
        elif is_to_delete:

            for title in args:
                matched_todo = find_todo_by_title(db_connection, config, title, defined_alarm)

                if is_to_print_json:
                    delete_todo(db_connection, config, title, defined_alarm)
                    print_in_json(matched_todo)
                else:
                    delete_todo(db_connection, config, title, defined_alarm)
                    pretty_print(matched_todo, config)

        elif is_to_display_newest:
            matched_todo = find_newest_todo(db_connection)

            if is_to_print_json:
                print_in_json(matched_todo)
            else:
                paginate(matched_todo, config)
        elif is_to_display_older:
            matched_todo = find_oldest_todo(db_connection)

            if is_to_print_json:
                print_in_json(matched_todo)
            else:
                paginate(matched_todo, config)
        else:
            matched_todo = find_all(db_connection)
            paginate(matched_todo, config)

        db_connection.close()

    except KeyboardInterrupt as e:
        sys.exit(0)


if __name__ == '__main__':
    main()
