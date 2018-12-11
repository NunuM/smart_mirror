#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sched
import time
import uuid
import os
import socket
import json
import datetime
import threading
import smtplib
import configparser
from email.mime.text import MIMEText


class EventManager:
    def __init__(self, config):
        """
        :param ConfigParser config:
        """
        self.events = {}
        self.scheduler = sched.scheduler(time.time, time.sleep)
        self.config = config
        self._semaphore = threading.Semaphore(0)
        self._stop = False

    def __len__(self):
        return len(self.events)

    def __getitem__(self, item):
        """
        :param uuid item:
        :return:
        """
        return self.events.get(item)

    def connect_to_email_server(self) -> smtplib.SMTP:
        """
        Exceptions not handled
        :return:
        """
        email_server = smtplib.SMTP_SSL(self.config.get('email', 'host'), self.config.get('email', 'port'))
        email_server.ehlo()
        email_server.login(self.config.get('email', 'user'), self.config.get('email', 'password'))

        return email_server

    def dispatch_event(self, message):
        """
        :param dict message:
        :return:
        """
        email_from = self.config.get('email', 'user')
        email_to = self.config.get('organizer', 'recipients')

        msg = MIMEText("Thank you for using organizer.")
        msg['Subject'] = message
        msg['From'] = email_from
        msg['To'] = email_to

        email_server = self.connect_to_email_server()
        email_server.sendmail(email_from, email_to, msg.as_string())

        email_server.close()

    def run(self):
        print("Running...")
        self._semaphore.acquire()
        if not self._stop:
            print("Unlocked")
            self.scheduler.run(blocking=True)
            print("Alarm")

            return self.run()

    def stop_and_exit(self):
        self._stop = True
        self._semaphore.release()

    def queue_notification_event(self, on, message):
        """

        :param str on:
        :param dict message:
        :return:
        """
        date_time = datetime.datetime.strptime(on, "%Y-%m-%d %H:%M")
        required_time = time.mktime(date_time.timetuple())
        event = self.scheduler.enterabs(required_time, 1, self.dispatch_event, (message,))
        generated_uuid = uuid.uuid1()
        self.events[generated_uuid] = event
        self._semaphore.release()

        return generated_uuid.__str__()

    def cancel_event(self, uid) -> bool:
        """
        :param UUID uid:
        :return:
        """
        event = self.events.get(uid)
        if event is not None:
            try:
                self.scheduler.cancel(event)
                return True
            except ValueError:
                return False
        return False


class CommunicationManager:
    CREATE = 0
    DELETE = 1
    QUIT = 2

    def __init__(self, server_address):
        """

        :param str server_address:
        """
        self.server_address = server_address
        self.check_server_address()
        self.sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.ticket = 1

    def check_server_address(self):
        try:
            os.unlink(self.server_address)
        except OSError:
            if os.path.exists(self.server_address):
                raise ValueError('Please provide a valid socket address')

    def run(self, event_manager, prepare=True, stop=False):
        """

        :param prepare:
        :param EventManager event_manager:
        :param stop:
        :return:
        """
        if prepare:
            self.sock.bind(self.server_address)
            self.sock.listen(1)

        connection, client_address = self.sock.accept()
        try:
            while True:
                size = connection.recv(4)
                action = connection.recv(2)

                try:
                    msg_size = int(size)
                    action = int(action)
                except ValueError:
                    break

                if msg_size > 2:
                    message = connection.recv(msg_size)
                    try:
                        decoded_message = json.loads(message, encoding='utf-8')
                    except:
                        break
                else:
                    decoded_message = {}

                if action == self.CREATE:

                    event_id = event_manager.queue_notification_event(decoded_message.get('alarm'),
                                                                      decoded_message.get('message'))

                    response = json.dumps(
                        {
                            'success': True if event_id is not None else False,
                            'id': event_id,
                            'ticket': self.ticket
                        })

                elif action == self.DELETE:

                    str_uid = decoded_message.get('id')
                    if str_uid:
                        result = event_manager.cancel_event(uuid.UUID(str_uid))
                    else:
                        result = False

                    response = json.dumps({'success': result, 'ticket': self.ticket})

                elif action == self.QUIT:
                    stop = True
                    response = json.dumps({'success': True, 'ticket': self.ticket})
                else:
                    break

                response_len = str(len(response)).zfill(4)
                srt_response = '{}{}'.format(str(response_len), response)

                while connection.sendall(str.encode(srt_response, encoding='utf-8')) is None:
                    break

                break
        finally:
            connection.close()
            self.ticket += 1
            if not stop:
                self.run(event_manager, False)


def main():
    config = configparser.ConfigParser(os.environ)
    config.read("../config.cfg")

    event_manger = EventManager(config)

    t1 = threading.Thread(target=event_manger.run)
    t1.start()

    communication_manager = CommunicationManager("./test")
    communication_manager.run(event_manger)
    event_manger.stop_and_exit()


if __name__ == '__main__':
    main()
