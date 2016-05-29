from data_structure.queue import Queue


def find_escape_position(total, count):
    q = Queue()
    for i in xrange(total):
        q.enqueue(i+1)

    while q.size() > 1:
        for i in xrange(count-1):
            item = q.dequeue()
            q.enqueue(item)
        q.dequeue()

    return q.dequeue()
