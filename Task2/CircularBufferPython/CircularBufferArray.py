class CircularBufferArray:
    def __init__(self, size):
        self._size = size
        self._buffer = [None] * size
        self._head_index = 0
        self._tail_index = 0

    def push(self, value):
        self._buffer[self._tail_index] = value
        self._tail_index = self._get_next_index(self._tail_index)

    @property
    def head(self):
        return self._buffer[self._head_index]

    @head.setter
    def head(self, value):
        self._buffer[self._head_index] = value

    def next(self):
        self._head_index = self._get_next_index(self._head_index)

    def get_capacity(self):
        return self.size

    def _get_next_index(self, index):
        return (index + 1) % self._size
