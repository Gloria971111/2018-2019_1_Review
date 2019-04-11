import pprint as pt
import matplotlib as plt

class TreeNode(object):
    def __init__(self,name):
        self.name=name
        self.children=[]

class MultiTree(object):
    '''
    实现树的增删改查
    '''
    def __init__(self):
        