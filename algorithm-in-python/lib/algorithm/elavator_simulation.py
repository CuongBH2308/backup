#
# Goal:
# Simulate the elavators at Kerry Park side office, to get the average waiting
# time to get upstairs
#
# Simulation:
# The general way to design a simuation is like:
# 1. loop for a certain number of seconds (3600 seconds here)
# 2. for each second, tick() to update the state of all related objects
# 3. use a list to store the final result (waiting_list)
#

import sys
# sys.path.append("D:\\Source\\GitHub\\algorithm-in-python\\lib")

# waiting_number, elevator.take()
import random
from data_structure.queue import Queue


class Elevator(object):
    def __init__(
            self, capacity=24, num_of_floor=13, seconds_per_floor=2,
            total_stay_on_1st_floor=8, delay_while_stop=5, floors_per_stop=4,
            out_per_stop=4):
        self.cur_floor = 1
        self.cur_size = 0
        self.move = self.move_up
        self.tick_for_floor_change = 0
        self.tick_for_stop = 0
        self.capacity = capacity
        self.num_of_floor = num_of_floor
        self.wait_on_1st_floor = 0
        self.total_stay_on_1st_floor = total_stay_on_1st_floor
        self.seconds_per_floor = seconds_per_floor
        self.delay_while_stop = delay_while_stop
        self.floors_per_stop = floors_per_stop
        self.out_per_stop = out_per_stop

    def move_up(self):
        self.cur_floor += 1

    def move_down(self):
        self.cur_floor -= 1

    def is_available(self):
        return self.cur_floor == 1

    def tick(self):
        if self.tick_for_stop > 0:
            self.tick_for_stop += 1
            if self.tick_for_stop == self.delay_while_stop:
                self.tick_for_stop = 0
            else:
                return

        self.wait_on_1st_floor = self.wait_on_1st_floor + 1
        if self.wait_on_1st_floor == self.total_stay_on_1st_floor:
            self.wait_on_1st_floor = 0
        else:
            return

        self.tick_for_floor_change = self.tick_for_floor_change + 1
        if self.tick_for_floor_change == self.seconds_per_floor:
            self.tick_for_floor_change = 0
            if self.cur_floor == self.num_of_floor:
                self.move = self.move_down
                self.cur_size = 0
            if self.cur_floor == 1:
                self.move = self.move_up

            self.move()

            # stopped?
            if random.randint(1, self.floors_per_stop) == 4:
                self.tick_for_stop = 1
                self.cur_size -= random.randint(1, self.out_per_stop)
                if self.cur_size <= 0:
                    self.cur_size = 0
                    self.move = self.move_down
                return

    def take(self, person_queue, cur_time, waiting_list):
        for i in xrange(self.capacity):
            if not person_queue.is_empty():
                p = person_queue.dequeue()
                self.cur_size += 1
                waiting_list.append(cur_time - p.arrived_time)


class Person(object):
    def __init__(self, arrived_time):
        self.arrived_time = arrived_time


def simulation():
    person_queue = Queue()
    for i in xrange(10):
        person_queue.enqueue(Person(0))

    waiting_list = []

    elevators = []
    for i in xrange(6):
        elevators.append(Elevator())

    def new_comer(time):
        # every seconds comes 1 to 5 person
        for i in xrange(random.randint(1, 6)):
            person_queue.enqueue(Person(time))

    for sec in xrange(3600):
        new_comer(sec)
        for e in elevators:
            if e.is_available() and not person_queue.is_empty():
                e.take(person_queue, sec, waiting_list)

            e.tick()
    print "Average waiting time on 1st floor: %f" % \
        (sum(waiting_list) / float(len(waiting_list)))
