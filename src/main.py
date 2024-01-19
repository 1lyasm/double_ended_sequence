# split data in half, reverse first half and
# store in a list, and store second half in a list

class DESequence:
    def __init__(self):
        self.n = 0
        self.__lft = []
        self.__rgt = []

    def build(self, lst, n):
        if len(lst) == 0:
            self.__lft.reverse()
            return self
        self.n += 1
        if self.n <= n // 2:
            self.__lft.append(lst[0])
        else:
            self.__rgt.append(lst[0])
        return self.build(lst[1:], n)

    def get_at(self, idx):
        return self.__lft[len(self.__lft) - 1 - idx] if (
            idx < len(self.__lft)) else self.__rgt[
            idx - len(self.__lft)]

    def insertl(self, item):
        self.n += 1
        self.__rgt.append(item)
        print(f"Inserted {item} to the end")

    def insertf(self, item):
        self.n += 1
        self.__lft.append(item)
        print(f"Inserted {item} to the front")

    def deletel(self):
        if len(self.__rgt) <= 0:
            self.rebuild([], self.n)
        self.n -= 1
        item = self.__rgt.pop()
        print(f"Deleted last element {item}")
        return item

    def deletef(self):
        if len(self.__lft) <= 0:
            self.__rgt.reverse()
            self.rebuild([], self.n)
        self.n -= 1
        item = self.__lft.pop()
        print(f"Deleted first element {item}")
        return item

    def rebuild(self, lst, n):
        if self.n <= 0:
            self.build(lst, len(lst))
            return
        self.n -= 1
        if len(self.__lft) > 0:
            lst.append(self.__lft[-1])
            self.__lft.pop()
        else:
            lst.append(self.__rgt[-1])
            self.__rgt.pop()
        self.rebuild(lst, n)

def print_all(d):
    print("Sequence: ", end="")
    for i in range(d.n):
        print(d.get_at(i), end=" ")
    print("\n")

def main():
    lst = [1, 2, 3, 4, 5, 6]
    d = DESequence().build(lst, len(lst))
    print_all(d)
    for i in range(13, 20):
        d.insertl(i)
    print_all(d)

    lst = [1, 2, 3, 4, 5, 6]
    d = DESequence().build(lst, len(lst))
    for i in range(10):
        d.insertf(-i)
    print_all(d)

    for i in range(3):
        d.deletel()
    print_all(d)

    for i in range(10):
        d.deletef()
    print_all(d)

if __name__ == "__main__":
    main()
