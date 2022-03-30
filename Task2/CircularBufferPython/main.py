from CircularBufferList import CircularBufferList
from CircularBufferArray import CircularBufferArray

def main():
    cba = CircularBufferList()
    cba.push(54)
    cba.push(45)

    print(cba.head)
    cba.next()
    print(cba.head)
    cba.next()
    print(cba.head)
    cba.next()
    print(cba.head)

    cba.head = 5
    print(cba.head)
    cba.next()
    print(cba.head)
    cba.next()
    print(cba.head)
    cba.next()
    print(cba.head)

main()
