import xml.etree.ElementTree as ET
import re
import sqlite3
import json
import datetime
import logging
import ConfigParser
import getopt
import sys
import os.path
import logging.config
import requests


def usage():
    print """USAGE: pirate [OPTIONS]... [MOVIE]...
    
    Search and download movies.
    
    -b, --brief         print movie with partial attributes 
    -g, --genre         list all movies by genre 
    -i, --interactive   search for films in interactive mode
    -c, --config        use this config over the default.
    -r, --recent        check and persist new movies.
    -j, --json          print as json
    -h, --help          print this message and exits.
    """

    return True


def init_database(config):
    """
    Create database connection, and required tables
    :param config:
    :return: sqlite connection
    """
    db_name = config.get('sqlite', 'name')
    db_path = config.get('sqlite', 'abs_path')

    db_filename = os.path.join(db_path, db_name)

    conn = sqlite3.connect(db_filename)

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

    return conn


def search_movies_by_genre(conn, genre):
    """
    Perform a search by movie genre
    :param conn: sqlite connection instance
    :param genre: string
    :return: list of matched movies
    """
    query = """SELECT * FROM movies WHERE LOWER(genre) LIKE '%{}%'""".format(genre.lower())
    cur = conn.execute(query)

    return [dict((cur.description[i][0], value) \
                 for i, value in enumerate(row)) for row in cur.fetchall()]


def search_movies_by_tittle(conn, movie_title):
    """
    Perform a search by movie title
    :param conn: sqlite connection instance
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
    :param conn: sqlite connection
    :param movie_title: string
    :return: boolean
    """
    query = """SELECT COUNT(*) AS counter FROM movies WHERE LOWER(title) LIKE '{}'""".format(movie_title.lower())

    return conn.execute(query).fetchone()[0] > 0


def insert_into_database(conn, movies, in_batch=True):
    """
    Insert into database a given list of movies
    :param conn: database connection
    :param movies: list of tuples
    :param in_batch: boolean
    :return: boolean
    """
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
            logging.getLogger('pirate').error("Error on batch movies saving", movies, e)
    else:
        for movie in movies:
            try:
                conn.execute(query, movie)
            except Exception as e:
                logging.getLogger('pirate').error("Error on saving movie", movie, e)

    conn.commit()

    return True


def make_http_get_request(url):
    """
    Performs a HTTP GET request.
    :param url: string
    :return: body as string
    """
    response = requests.get(url)

    if response.status_code is not 200:
        logging.getLogger('pirate').error("Could not make GET request. status_code {}".format(response.status_code))
        raise ValueError("Must be a valid response from remote server")

    return response.text


def parse_tpb_xml_feed(feed):
    """
    Iterates over a xml containing the movies xml feed
    :param feed: string
    :return: tuple containing the title, quality and magnet of the movie
    """
    container = []

    root = ET.fromstring(feed)

    for items in root.findall(".//item"):
        original_title = items.find("title").text
        magnet = items.find("link").text
        grouped = re.search(r'(.*)(\(?20[0-9][0-9][\)|\.]?)(.*)', original_title.replace('.', ' '))
        if len(grouped.groups()) is 3:
            title = grouped.group(1).strip()
            quality = grouped.group(3).strip()
        else:
            title = grouped.group(0)
            quality = grouped.group(0)
        container.append((title, quality, original_title, magnet))

    return container


def prepare_movie_db_tuple(movie, metadata):
    """
    Merges tuple and json information resulting in a tuple with
    filed required to be inserted into the database
    :param movie: tuple
    :param metadata: json
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


def download_recent(db_connection, configs):
    """
    Download xml feed, askng to the db if each movie
    entry already exists into datase, if not,
    insert it.
    :param db_connection: database connection
    :param configs:
    :return: json of inserted movies
    """
    inserted_movies = []
    movies_to_insert = []

    feed = make_http_get_request(configs.get('piratebay', 'feed_url'))

    movies = parse_tpb_xml_feed(feed)

    for movie in movies:
        movie_title = movie[0]
        if does_movie_exists(db_connection, movie_title) is False:
            str_meta = make_http_get_request(configs.get('omdbapi', 'url').format(movie_title.replace(' ', '+')))
            json_meta = json.loads(str_meta)
            db_row = prepare_movie_db_tuple(movie, json_meta)
            movies_to_insert.append(db_row)

            json_meta['Quality'] = movie[2]
            json_meta['magnet'] = movie[1]
            json_meta['Title'] = movie[0]

            inserted_movies.append(json_meta)

    if len(movies_to_insert) != 0:
        insert_into_database(db_connection, movies_to_insert, False)

    return inserted_movies


def print_in_json(movies, is_brief=False, config=None):
    """
    Prints json string to stdout
    :param movies: array of movies
    :param is_brief: boolean
    :param config
    :return: True
    """
    valid_fields = []

    if config is not None:
        valid_fields = config.get('pirate', 'brief_fields').split(',')

    for movie in movies:
        if is_brief and len(valid_fields) > 0:
            print json.dumps({k: movie[k] for k in set(valid_fields) & set(movie.keys())})
        else:
            print json.dumps(movie)

    return True


def petty_print(movies, is_brief=False, config=None):
    """
    Column movie print
    :param movies: array of movies
    :param is_brief: boolean
    :param config
    :return: True
    """
    valid_fields = []

    if config is not None:
        valid_fields = config.get('pirate', 'brief_fields').split(',')

    for movie in movies:
        print '-' * 100
        for key in sorted(movie):
            if is_brief and len(valid_fields) > 0 and key not in valid_fields:
                continue
            print "{0:15}| {1:<25} ".format(unicode(key[0].upper() + key[1:]).encode('utf-8'),
                                            unicode(movie[key]).encode('utf-8'))
        print '-' * 100
    print ""
    return True


def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hjbric:g:",
                                   ["brief", "genre", "interactive", "json", "help", "recent", "config="])
    except getopt.GetoptError as err:
        print str(err)
        sys.exit(0)

    is_check_recent = False
    is_json = False
    is_interactive = False
    is_genre = False
    is_brief = False
    genre = None
    config_filename = "/usr/share/pirate/config.cfg"

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
                print "Configuration file {} not found, using the default".format(a)
        elif o in ("-g", "--genre"):
            is_genre = True
            genre = a
        else:
            print "Option {} is unknown".format(o)

    config = ConfigParser.SafeConfigParser()

    try:
        config.read(config_filename)
    except ConfigParser.ParsingError as e:
        error_string = "Could not parse config file {}".format(config_filename)
        print error_string + str(e)
        sys.exit(1)

    try:
        logging.config.fileConfig(config_filename)
    except Exception as e:
        print str(e)

    db_connection = init_database(config)

    if is_check_recent:
        try:
            inserted = download_recent(db_connection, config)
            if len(inserted) > 0:
                if is_json:
                    print_in_json(inserted, is_brief, config)
                else:
                    petty_print(inserted, is_brief, config)
            elif is_json is False:
                print "No new movies were found"
        except Exception as e:
            print str(e)
    elif is_interactive:
        search_token = ""

        while search_token.lower() != "q":
            search_token = raw_input("title:")
            if search_token.lower() != "q":
                matched_movies = search_movies_by_tittle(db_connection, search_token)
                petty_print(matched_movies, is_brief, config)
            else:
                break
    elif is_genre:
        matched_movies = search_movies_by_genre(db_connection, genre)
        current = 0
        num_movies = len(matched_movies)
        if is_json:
            print_in_json(matched_movies, is_brief, config)
        else:
            for movie in matched_movies:
                print "Results for the genre: {}".format(genre)
                petty_print([movie], is_brief, config)
                current += 1
                char = raw_input("{} in total of {}. Press enter to continue or q to exit.".format(current, num_movies))
                if char == "q":
                    break
                os.system('cls' if os.name == 'nt' else 'clear')
    else:
        for search in args:
            matched_movies = search_movies_by_tittle(db_connection, search)
            if is_json:
                print_in_json(matched_movies, is_brief, config)
            else:
                print "Results for query: {}".format(search)
                petty_print(matched_movies, is_brief, config)


if __name__ == '__main__':
    main()
