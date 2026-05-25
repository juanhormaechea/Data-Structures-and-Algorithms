import unittest
import queues

class TestEnqueue(unittest.TestCase):
    def test_empty_queue(self):
        queue = queues.Queue()
        queue.enqueue(1)
        self.assertEqual(1, queue.queueSize())
        self.assertEqual(queue.front, queue.back)
        self.assertEqual(1, queue.front.data)
        self.assertIsNone(queue.front.next)

    def test_full_queue(self):
        queue = queues.Queue()
        for i in range(0, 10):
            queue.enqueue(i)
        self.assertEqual(10, queue.queueSize())
        head = queue.front
        for i in range(0, 10):
            self.assertEqual(i, head.data)
            head = head.next
    

class TestDequeue(unittest.TestCase):
    def test_empty_queue(self):
        queue = queues.Queue()
        self.assertIsNone(queue.dequeue())
        self.assertIsNone(queue.front)
        self.assertIsNone(queue.back)
        self.assertEqual(0, queue.queueSize())
    
    def test_one_node(self):
        queue = queues.Queue()
        queue.enqueue(1)
        self.assertEqual(1, queue.dequeue())
        self.assertEqual(0, queue.queueSize())
        self.assertIsNone(queue.front)
        self.assertIsNone(queue.back)
    
    def test_full_queue(self):
        queue = queues.Queue()
        for i in range(0, 10):
            queue.enqueue(i)
        self.assertEqual(0, queue.dequeue())
        self.assertEqual(9, queue.queueSize())
        self.assertEqual(1, queue.front.data)
        self.assertEqual(9, queue.back.data)


class TestPeek(unittest.TestCase):
    def test_empty_queue(self):
        queue = queues.Queue()
        self.assertIsNone(queue.peek())
    
    def test_one_node(self):
        queue = queues.Queue()
        queue.enqueue(1)
        self.assertEqual(1, queue.peek())
        self.assertEqual(1, queue.queueSize())
    
    def test_full_queue(self):
        queue = queues.Queue()
        for i in range(0, 10):
            queue.enqueue(i)
        self.assertEqual(0, queue.peek())
        self.assertEqual(10, queue.queueSize())
    

class TestIsEmpty(unittest.TestCase):
    def test_empty_queue(self):
        queue = queues.Queue()
        self.assertTrue(queue.isEmpty())
    
    def test_non_empty_queue(self):
        queue = queues.Queue()
        for i in range(0, 10):
            queue.enqueue(i)
            self.assertFalse(queue.isEmpty())

    
  




if __name__ == '__main__':
    unittest.main()