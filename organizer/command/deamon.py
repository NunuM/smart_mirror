#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sched
import time
import uuid
import os
import socket
import json
import datetime


class EventManager:
    def __init__(self):
        self.events = {}
        self.scheduler = sched.scheduler(time.time, time.sleep)

    def __len__(self):
        return len(self.events)

    def __getitem__(self, item):
        """
        :param uuid item:
        :return:
        """
        return self.events.get(item)

    @staticmethod
    def dispatch_event(message):
        """
        :param dict message:
        :return:
        """
        os.system("notifier -s {} {}".format(message.get('title'),
                                             message.get('body')))

    def queue_notification_event(self, on, message):
        """

        :param str on:
        :param dict message:
        :return:
        """
        date_time = datetime.datetime.strptime(on, "%Y-%m-%d %H:%M")
        required_time = time.mktime(date_time.timetuple())
        event = self.scheduler.enterabs(required_time, 1, self.dispatch_event, (message,))

        return event

    def cancel_event(self, id):
        event = self.events.get(id)
        if event is not None:
            self.scheduler.cancel(event)
            return True
        return False


class CommunicationManager:
    CREATE = 0
    DELETE = 1

    def __init__(self, server_address):
        """

        :param str server_address:
        """
        self.server_address = server_address
        self.check_server_address()
        self.sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.ticket = 0

    def check_server_address(self):
        try:
            os.unlink(self.server_address)
        except OSError:
            if os.path.exists(self.server_address):
                raise ValueError('Please provide a valid socket address')

    def run(self, event_manager):
        """

        :param EventManager event_manager:
        :return:
        """
        self.sock.bind(self.server_address)
        self.sock.listen(1)

        connection, client_address = self.sock.accept()
        try:
            while True:
                size = connection.recv(4)
                action = int(connection.recv(1))
                message = connection.recv(int(size))
                decoded_message = json.loads(message, encoding='utf-8')

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
                    result = event_manager.cancel_event(decoded_message.get('id'))
                    response = json.dumps({'success': result, 'ticket': self.ticket})
                else:
                    break

                response_len = str(len(response)).zfill(4)
                connection.sendall(response_len + response)
                break
        finally:
            connection.close()
            self.ticket += 1
            self.run(event_manager)


def main():
    event_manger = EventManager()
    communication_manager = CommunicationManager("./test")
    communication_manager.run(event_manger)


if __name__ == '__main__':
    main()
