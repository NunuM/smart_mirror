# -*- coding: utf-8 -*-

import xml.etree.ElementTree as ET
import re
import sqlite3
import json
import datetime
import requests
import configparser
import getopt
import sys
import os.path


def usage():
    print("""\033[1mUSAGE:\033[0m blockbuster [OPTIONS]... [MOVIE]...

    Query movies information by populating the local database from
    XML feeds that you like. Invoke the program using only the option -r,
    then you can query the movies that you want. You must execute
    this action on regular basis.  
    
    You must set your omdbapi api key by typing:
    $ snap set blockbuster omdbapi="you-api-key"

    You can also change the XML source feed since the source follows
    the syntax of having an XML with title and link tags, repeated 
    within of an item tag, eg:
        ... 
        <item>
            <title></title>
            <link></link>
        </item>
        ...
    $ snap set blockbuster feed="https://mymoviessource.com/rss?category=movies"

    To see your snap configuration, you can query:
    $ snap get blockbuster omdbapi

\033[1mOPTIONS:\033[0m
    -b, --brief         print movie with partial attributes, 
		                this works along others options, such as: -j and/or -g.
    -g, --genre         list all movies by genre.
    -i, --interactive   search for films in interactive mode.
    -c, --config        use this config over the default.
    -r, --recent        check and persist new movies.
    -l, --list          list N recently added movies.
    -j, --json          print as json.
    -p, --paginate      Paginate by N recent added movies.
    -h, --help          print this message and exits.

\033[1mEXAMPLES:\033[0m
    Search all action movies and I only want see a brief summary.
    $ blockbuster -b -g action

    Search movies by name and print as JSON.
    $ blockbuster -b -j "The Movies"

    Check if there are new movies, but I override current configuration 
    by this configuration:
    $ blockbuster -c /home/my.cfg -r

\033[1mCREDITS:\033[0m
    Application icon made by Freepik - http://www.freepik.com

\033[1mPROJECT:\033[0m
    GitHub - https://github.com/NunuM/movies_command

    		Made with love by nunum
    """)

    return True


def init_database(config):
    """
    Create database connection, and required tables
    :param configparser.ConfigParser config:
    :return: sqlite connection
    """
    db_name = config.get('sqlite', 'name')

    user_dir = config.get('sqlite', 'rel_path')
    db_path = os.path.join(user_dir, db_name)

    conn = sqlite3.connect(db_path)

    conn.execute("""CREATE TABLE IF NOT EXISTS movies 
                        ( title         TEXT PRIMARY KEY,
                          quality       TEXT,
                          originaltitle TEXT,
                          magnet        TEXT,
                          year          INT,
                          rated         TEXT,
                          released      TEXT,
                          runtime       TEXT,
                          genre         TEXT,
                          director      TEXT,
                          writer        TEXT,
                          actors        TEXT,
                          plot          TEXT,
                          language      TEXT,
                          country       TEXT,
                          awards        TEXT,
                          poster        TEXT,
                          metascore     TEXT,
                          imdbrating    REAL,
                          imdbvotes     TEXT,
                          imdbid        TEXT,
                          type          TEXT,
                          dvd           TEXT,
                          boxoffice     TEXT,
                          production    TEXT,
                          website       TEXT,
                          inserted      DATETIME)""")

    conn.execute("CREATE INDEX IF NOT EXISTS idx_inserted on movies(inserted)")

    return conn


def search_movies_by_genre(conn, genre):
    """
    Perform a search by movie genre
    :param sqlite3.Connection conn: instance
    :param str genre: string
    :return: list of matched movies
    """
    query = """SELECT * FROM movies WHERE LOWER(genre) LIKE '%{}%'""".format(genre.lower())
    cur = conn.execute(query)

    return [dict((cur.description[i][0], value) \
                 for i, value in enumerate(row)) for row in cur.fetchall()]


def recent_movies(conn, number):
    """

    :param sqlite3.Connection conn:
    :param int number:
    :return:
    """

    cur = conn.execute("SELECT * FROM movies ORDER BY inserted DESC LIMIT {}".format(number))

    return [dict((cur.description[i][0], value) \
                 for i, value in enumerate(row)) for row in cur.fetchall()]


def paginate_movies(conn, item_per_page, page):
    """
    :param sqlite3.Connection conn:
    :param int item_per_page:
    :param int page:
    :return:
    """
    start = page * item_per_page
    end = start + item_per_page

    cur = conn.execute("SELECT * FROM movies ORDER BY inserted DESC LIMIT {}, {}".format(start, end))

    return [dict((cur.description[i][0], value) \
                 for i, value in enumerate(row)) for row in cur.fetchall()]


def search_movies_by_tittle(conn, movie_title):
    """
    Perform a search by movie title
    :param sqlite3.Connection conn: instance
    :param movie_title: string
    :return: list of matched movies
    """
    query = """SELECT * FROM movies WHERE LOWER(title) LIKE '%{}%'""".format(movie_title.lower())
    cur = conn.execute(query)

    return [dict((cur.description[i][0], value) \
                 for i, value in enumerate(row)) for row in cur.fetchall()]


def does_movie_exists(conn, movie_title):
    """
    Verify if movies exists given a name
    :param sqlite3.Connection conn: instance
    :param str movie_title:
    :return: boolean
    """
    query = """SELECT COUNT(*) AS counter FROM movies WHERE LOWER(title) LIKE '{}'""".format(movie_title.lower())

    return conn.execute(query).fetchone()[0] > 0


def insert_into_database(conn, movies, in_batch=True, is_verbose=False):
    """
    Insert into database a given list of movies
    :param sqlite3.Connection conn: database connection
    :param list movies: list of tuples
    :param in_batch: boolean
    :param is_verbose: boolean
    :return: boolean
    """
    result = True
    query = """INSERT INTO movies(title,
                                  quality,
                                  originaltitle,
                                  magnet,
                                  `year`,
                                  rated,
                                  released,
                                  runtime,
                                  genre,
                                  director,
                                  writer,
                                  actors,
                                  plot,
                                  `language`,
                                  country,
                                  awards,
                                  poster,
                                  metascore,
                                  imdbrating,
                                  imdbvotes,
                                  imdbid,
                                  `type`,
                                  dvd,
                                  boxoffice,
                                  production,
                                  website,
                                  inserted)
               VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)"""

    if in_batch:
        try:
            conn.executemany(query, movies)
        except Exception as e:
            result = False
            if is_verbose:
                print(str(e))

    else:
        for movie in movies:
            try:
                conn.execute(query, movie)
            except Exception as e:
                result = False
                if is_verbose:
                    print("Movie {} was not inserted, reason: {}".format(movie[0] if len(movie) > 0 else "Unknown",
                                                                         str(e)))

    conn.commit()

    return result


def make_http_get_request(url):
    """
    Performs a HTTP GET request.
    :param str url: string
    :return: body as string
    """
    response = requests.get(url)

    if response.status_code is not 200:
        raise ValueError(url + " not return OK response, status code :" + str(response.status_code))

    return response.text


def parse_tpb_xml_feed(feed):
    """
    Iterates over a xml containing the movies xml feed
    :param str feed:
    :return: tuple containing the title, quality and magnet of the movie
    """
    container = []

    root = ET.fromstring(feed)

    for items in root.findall(".//item"):
        original_title = items.find("title").text

        if original_title is not None and len(original_title) > 0:
            original_title = original_title.replace('\'', '´')
        else:
            continue

        magnet = items.find("link").text
        grouped = re.search(r'(.*)(\(?[0-9]{4}[\)?|\.]? )(.*)', original_title.replace('.', ' '))
        if grouped is not None and len(grouped.groups()) is 3:
            title = grouped.group(1).strip()
            quality = grouped.group(3).strip()
        else:
            title = original_title
            quality = original_title
        container.append((title, quality, original_title, magnet))

    return container


def prepare_movie_db_tuple(movie, metadata):
    """
    Merges tuple and json information resulting in a tuple with
    filed required to be inserted into the database
    :param tuple movie: tuple
    :param dict metadata: json
    :return: tuple
    """
    json_object = metadata

    imdb_rating = json_object.get("imdbRating")

    if imdb_rating is not None:
        try:
            json_object['imdbRating'] = float(imdb_rating)
        except ValueError:
            json_object['imdbRating'] = 0.0

    json_object['inserted'] = str(datetime.datetime.now())

    return movie + (json_object.get('Year'),
                    json_object.get('Rated'),
                    json_object.get('Released'),
                    json_object.get('Runtime'),
                    json_object.get('Genre'),
                    json_object.get('Director'),
                    json_object.get('Writer'),
                    json_object.get('Actors'),
                    json_object.get('Plot'),
                    json_object.get('Language'),
                    json_object.get('Country'),
                    json_object.get('Awards'),
                    json_object.get('Poster'),
                    json_object.get('Metascore'),
                    json_object.get('imdbRating'),
                    json_object.get('imdbVotes'),
                    json_object.get('imdbID'),
                    json_object.get('Type'),
                    json_object.get('DVD'),
                    json_object.get('BoxOffice'),
                    json_object.get('Production'),
                    json_object.get('Website'),
                    json_object.get('inserted'))


def download_recent(db_connection, configs, is_verbose=False):
    """
    Download xml feed, asking to the db if each movie
    entry already exists into database, if not,
    insert it.
    :param sqlite3.Connection db_connection: instance
    :param configparser.ConfigParser configs:
    :param is_verbose: boolean
    :return: json of inserted movies
    """
    inserted_movies = []
    movies_to_insert = []

    try:
        feed = make_http_get_request(configs.get('rsssource', 'feed_url'))
    except ValueError as e:
        print("Cannot continue due TBP feed failure, reason:" + str(e))
        sys.exit(1)

    movies = parse_tpb_xml_feed(feed)

    for movie in movies:
        movie_title = movie[0]
        json_meta = {'Quality': movie[1], 'magnet': movie[3], 'Title': movie[0]}
        if is_verbose:
            print("check movie:" + movie_title.encode('ascii', 'replace').decode())
        if does_movie_exists(db_connection, movie_title) is False:
            try:
                str_meta = make_http_get_request(configs.get('omdbapi', 'url').format(movie_title.replace(' ', '+')))
                meta = json.loads(str_meta, encoding='utf-8')
                json_meta.update(meta)
            except Exception as e:
                if is_verbose:
                    print("Cannot pull movie metadata, reason:" + str(e))

            db_row = prepare_movie_db_tuple(movie, json_meta)
            movies_to_insert.append(db_row)
            inserted_movies.append(json_meta)

    if len(movies_to_insert) != 0:
        if is_verbose:
            print("Inserting " + str(len(movies_to_insert)) + " new movies")

        insert_into_database(db_connection, movies_to_insert, False, is_verbose)

    return inserted_movies


def print_in_json(movies, is_brief=False, config=None):
    """
    Prints json string to stdout
    :param list list movies:
    :param is_brief
    :param configparser.ConfigParser config
    :return: True
    """
    to_print = []
    valid_fields = []

    if config is not None:
        valid_fields = config.get('pirate', 'brief_fields').split(',')

    if is_brief and len(valid_fields) > 0:
        for movie in movies:
            to_print.append({k: movie[k] for k in set(valid_fields) & set(movie.keys())})
    else:
        to_print = movies

    print(json.dumps(to_print))

    return True


def petty_print(movies, is_brief=False, config=None):
    """
    Column movie print
    :param list movies: array of movies
    :param is_brief: boolean
    :param configparser.ConfigParser config:
    :return: True
    """
    valid_fields = []

    if config is not None:
        valid_fields = config.get('pirate', 'brief_fields').split(',')

    for movie in movies:
        print('-' * 100)
        for key in sorted(movie):
            if is_brief and len(valid_fields) > 0 and key not in valid_fields:
                continue
            print("{0:15}| {1:<25}".format((key[0].upper() + key[1:]),
                                           str(movie[key]).encode('ascii', 'replace').decode()))
        print('-' * 100)
    print("")
    return True


def paginate(movies, query, is_brief=False, config=None):
    """
    Paginate movies
    :param list movies:
    :param str query:
    :param is_brief: boolean
    :param configparser.ConfigParser config:
    :return: True
    """
    current = 0
    num_movies = len(movies)

    for movie in movies:
        print("Results for the query: {}".format(query))
        petty_print([movie], is_brief, config)
        current += 1
        char = input("{} in total of {}. Press enter to continue or q to exit.".format(current, num_movies))
        if char == "q":
            break
        os.system('cls' if os.name == 'nt' else 'clear')

    return True


def main():
    try:
        try:
            opts, args = getopt.getopt(sys.argv[1:], "hjbril:c:g:p:",
                                       ["brief",
                                        "genre",
                                        "interactive",
                                        "json",
                                        "help",
                                        "recent",
                                        "list",
                                        "paginate",
                                        "config="])
        except getopt.GetoptError as err:
            print(str(err))
            sys.exit(0)

        is_check_recent = False
        is_json = False
        is_interactive = False
        is_genre = False
        is_brief = False
        is_to_list = False
        is_to_paginate = False
        page_number = 0
        number_to_list = 20
        genre = None
        config_filename = os.path.join(os.environ['SNAP_DATA'], "config.cfg")

        for o, a in opts:
            if o in ("-h", "--help"):
                usage()
                sys.exit(0)
            elif o in ("-r", "--recent"):
                is_check_recent = True
            elif o in ("-j", "--json"):
                is_json = True
            elif o in ("-b", "--brief"):
                is_brief = True
            elif o in ("-i", "--interactive"):
                is_interactive = True
            elif o in ("-c", "--config"):
                if os.path.exists(a):
                    config_filename = a
                else:
                    print("Configuration file {} not found, using the default".format(a))
            elif o in ("-g", "--genre"):
                is_genre = True
                genre = a
            elif o in ("-l", "--list"):
                is_to_list = True

                try:
                    number_to_list = int(a)
                except ValueError as e:
                    pass
            elif o in ("-p", "--paginate"):
                is_to_paginate = True
                try:
                    page_number = int(a)
                except ValueError as e:
                    pass
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

        if is_check_recent:
            if not config.get('omdbapi', 'api_key') and not is_json:
                print(
                    "Please provide you omdbapi key by typing in your shell:'snap set blockbuster omdbapi=\"you-api-key\"'")
                if input("continue y/n?:") != 'y':
                    sys.exit(0)
            try:
                inserted = download_recent(db_connection, config, not is_json)
                if len(inserted) > 0:
                    if is_json:
                        print_in_json(inserted, is_brief, config)
                    else:
                        paginate(inserted, "Recent", is_brief, config)
                elif is_json is False:
                    print("No movies were added")
            except Exception as e:
                print(str(e))
        elif is_interactive:
            search_token = ""

            while search_token.lower() != "q":
                search_token = input("title:")
                if search_token.lower() != "q":
                    matched_movies = search_movies_by_tittle(db_connection, search_token)
                    paginate(matched_movies, search_token, is_brief, config)
                else:
                    break
        elif is_genre:
            matched_movies = search_movies_by_genre(db_connection, genre)
            if is_json:
                print_in_json(matched_movies, is_brief, config)
            else:
                paginate(matched_movies, genre, is_brief, config)
        elif is_to_list:
            if is_json:
                if is_to_paginate:
                    print_in_json(paginate_movies(db_connection, number_to_list, page_number))
                else:
                    print_in_json(recent_movies(db_connection, number_to_list), is_brief, config)
            else:
                if is_to_paginate:
                    paginate(paginate_movies(db_connection, number_to_list, page_number),
                             "Page {}".format(++page_number))
                else:
                    paginate(recent_movies(db_connection, number_to_list), '', is_brief, config)
        else:
            for search in args:
                matched_movies = search_movies_by_tittle(db_connection, search)
                if is_json:
                    print_in_json(matched_movies, is_brief, config)
                else:
                    paginate(matched_movies, search, is_brief, config)

        db_connection.close()
    except KeyboardInterrupt:
        sys.exit(0)


if __name__ == '__main__':
    main()
