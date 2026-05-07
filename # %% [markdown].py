# %% [markdown]
# # Trees and Tree Algorithms

# %% [markdown]
# ## 1. Binary Tree: List of Lists Representation

# %%
myTree = ['a',      # root
          ['b',
           ['d',['m',[],[]],[]], ['e',[],['n',[],[]]] ],
          ['c',
           ['f',[],[]], ['g',[],[]]]
          ]

# %%


# %%
myTree = ['a',      # root
          ['b',     # left subtree
           ['d',[],[]], ['e',[],[]] ],
          ['c',     # right subtree
           ['f',[],[]], []]
          ]

# %%
print(myTree)

# %%
print('left subtree = ', myTree[1])

# %%
print('root = ', myTree[0])

# %%
print('right subtree = ', myTree[2])

# %% [markdown]
# ## 1.1 BinaryTree Function

# %%
def BinaryTree(r):
    return [r, [], []]

# %%
def insertLeft(root,newBranch):
    t = root.pop(1)
    if len(t) > 1:
        root.insert(1,[newBranch,t,[]])
    else:
        root.insert(1,[newBranch, [], []])
    return root

# %%
def insertRight(root,newBranch):
    t = root.pop(2)
    if len(t) > 1:
        root.insert(2,[newBranch,[],t])
    else:
        root.insert(2,[newBranch,[],[]])
    return root

# %%
def getRootVal(root):
    return root[0]

def setRootVal(root,newVal):
    root[0] = newVal

def getLeftChild(root):
    return root[1]

def getRightChild(root):
    return root[2]

# %%
r = BinaryTree(3)

# %%
insertLeft(r,4)

# %%
insertLeft(r,5)

# %%
insertRight(r,6)

# %%
insertRight(r,7)

# %%
l = getLeftChild(r)

# %%
print(l)

# %%
setRootVal(l,9)

# %%
print(r)

# %%
insertLeft(l,11)

# %%
print(r)

# %% [markdown]
# ## Example - 모스 부호

# %%
class TNode:
    def __init__ (self, data, left, right):
        self.data = data
        self.left = left
        self.right = right

# %% [markdown]
# 모스부호 테이블

# %%
table =[('A', '.-'),    ('B', '-...'),  ('C', '-.-.'),  ('D', '-..'),
        ('E', '.'),     ('F', '..-.'),  ('G', '--.'),   ('H', '....'),
        ('I', '..'),    ('J', '.---'),  ('K', '-.-'),   ('L', '.-..'),
        ('M', '--'),    ('N', '-.'),    ('O', '---'),   ('P', '.--.'),
        ('Q', '--.-'),  ('R', '.-.'),   ('S', '...'),   ('T', '-'),
        ('U', '..-'),   ('V', '...-'),  ('W', '.--'),   ('X', '-..-'),
        ('Y', '-.--'),  ('Z', '--..') ]

# %%
def make_morse_tree():
    root = TNode( None, None, None )
    for tp in table :
        code = tp[1]
        node = root
        for c in code :
            if c == '.' :
                if node.left == None :
                    node.left = TNode (None, None, None)
                node = node.left
            elif c == '-' :
                if node.right == None :
                    node.right = TNode (None, None, None)
                node = node.right

        node.data = tp[0]
    return root

def decode(root, code):
    node = root
    for c in code :
        if c == '.' : node = node.left
        elif c=='-' : node = node.right
    return node.data

def encode(ch):
    idx = ord(ch)-ord('A')
    return table[idx][1]

# %%
ord('A')

# %%
morseCodeTree = make_morse_tree()
#str = input("입력 문장 : ")
str = "JBNU"
mlist = []
# Encoding : String --> Morse
for ch in str:
    code = encode(ch)
    mlist.append(code)

print("Morse Code: ", mlist)

# Decoding : Morse --> String
print("Decoding  : ", end='')
for code in mlist:
    ch = decode(morseCodeTree, code)
    print(ch, end='')
print()

# %%
class BinHeap:
    def __init__(self):
        self.heap_list = [0]
        self.current_size = 0

    def perc_up(self, i):
        while i // 2 > 0:
            if self.heap_list[i] < self.heap_list[i // 2]:
                tmp = self.heap_list[i // 2]
                self.heap_list[i // 2] = self.heap_list[i]
                self.heap_list[i] = tmp
        i = i // 2

    def insert(self, k):
        self.heap_list.append(k)
        self.current_size = self.current_size + 1
        self.perc_up(self.current_size)

    def min_child(self, i):
        if i * 2 + 1 > self.current_size:
            return i * 2
        else:
            if self.heap_list[i * 2] < self.heap_list[i * 2 + 1]:
                return i * 2
            else:
                return i * 2 + 1
    def perc_down(self, i):
        while (i * 2) <= self.current_size:
            mc = self.min_child(i)

            if self.heap_list[i] > self.heap_list[mc]:
                tmp = self.heap_list[i]
                self.heap_list[i] = self.heap_list[mc]
                self.heap_list[mc] = tmp

            i = mc

    def del_min(self):
        ret_val = self.heap_list[1]

        self.heap_list[1] = self.heap_list[self.current_size]
        self.current_size = self.current_size - 1

        self.heap_list.pop()
        self.perc_down(1)

        return ret_val

    def build_heap(self, a_list):
        i = len(a_list) // 2

        self.current_size = len(a_list)
        self.heap_list = [0] + a_list[:]
        while i > 0:
            self.perc_down(i)
            i = i - 1


  
    def heapsort(iterable):
        heap = BinHeap()

        for x in iterable:
            heap.insert(x)

        sorted_lst = []

        for _ in range(heap.current_size):
            sorted_lst.append(heap.del_min())

        return sorted_lst




