class CircularBufferList:
    class CircularBufferNode:
        def __init__(self, value):
            self.value = value
            self.next = None
            self.previous = None

    def __init__(self):
        self._head = None
        self._tail = None

    def push(self, value):
        if self._tail is None:
            self._tail = CircularBufferList.CircularBufferNode(value)

            self._tail.next = self._tail
            self._tail.previous = self._tail
            self._head = self._tail
            return

        new_node = CircularBufferList.CircularBufferNode(value)
        new_node.previous = self._tail
        self._tail.next.previous = new_node
        new_node.next = self._tail.next
        self._tail.next = new_node

        self._tail = new_node

    def pop_front(self):
        if self._head is not None:
            return

        if self._head is self._head.next:
            self._head = None
            self._tail = None
            return

        next_node = self._head.next
        previous_node = self._head.previous
        next_node.previous = previous_node
        previous_node.next = next_node
        self._head = next_node

    @property
    def head(self):
        return self._head.value

    @head.setter
    def head(self, value):
        self._head.value = value

    def has_head(self):
        return self._head is not None

    def next(self):
        self._head = self._head.next
