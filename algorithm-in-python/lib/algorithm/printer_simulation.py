from data_structure.queue import Queue
import random


class Printer(object):
    def __init__(self, ppm):
        self.pagerate = ppm  # page per minute
        self.currentTask = None
        self.timeRemaining = 0

    def tick(self):  # simulate a second passed
        if self.currentTask:
            self.timeRemaining = self.timeRemaining - 1
            if self.timeRemaining <= 0:
                self.currentTask = None

    def busy(self):
        return self.currentTask

    def startNext(self, newtask):
        self.currentTask = newtask
        self.timeRemaining = newtask.getPages() / float(self.pagerate) * 60


class Task(object):
    def __init__(self, time):
        self.timestamp = time  # created time
        self.pages = random.randrange(1, 21)

    def getStamp(self):
        return self.timestamp

    def getPages(self):
        return self.pages

    def waitTime(self, currenttime):
        return currenttime - self.timestamp


def simulation(numSeconds, pagesPerMinute):

    labprinter = Printer(pagesPerMinute)
    printQueue = Queue()
    waitingtimes = []

    for currentSecond in range(numSeconds):

        if newPrintTask():
            task = Task(currentSecond)
            printQueue.enqueue(task)

        if (not labprinter.busy()) and (not printQueue.is_empty()):
            nexttask = printQueue.dequeue()
            waitingtimes.append(nexttask.waitTime(currentSecond))
            labprinter.startNext(nexttask)

        labprinter.tick()

    averageWait = sum(waitingtimes) / len(waitingtimes)
    print("Finished tasks %3d  Average Wait %6.2f secs %3d tasks remaining." %
          (len(waitingtimes), averageWait, printQueue.size()))


def newPrintTask():
    # 10 students, 2 tasks per hour = 20tasks/hour = 1 task/180s
    num = random.randrange(1, 181)
    if num == 180:
        return True
    else:
        return False
