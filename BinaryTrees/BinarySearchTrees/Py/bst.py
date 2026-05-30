class Node:
    def __init__(self, data: int):
        self.data = data
        self.left_child: Node | None = None
        self.right_child: Node | None = None


class BST:
    def __init__(self):
        self.root: Node | None = None
    
    def insert(self, data: int) -> None:
        self.root = self.__insert(data, self.root)

    def __insert(self, data: int, root: Node | None) -> Node:
        if root is None:
            return Node(data)
        
        if data == root.data:
            return root
        
        if data < root.data:
            root.left_child = self.__insert(data, root.left_child)
        else:
            root.right_child = self.__insert(data, root.right_child)
        
        return root
    
    
    def __findParent(self, data: int, root: Node | None) -> Node | None:
        if root is None:
            return None
        
        if root.data == data:
            return None
        
        if (root.left_child is not None and root.left_child.data == data) or (root.right_child is not None and root.right_child.data == data):
            return root
        
        if root.data < data:
            return self.__findParent(data, root.right_child)
        
        return self.__findParent(data, root.left_child)
    

    def delete(self, data: int) -> None:
        if self.search(data) is None:
            return None
        else:
            self.root = self.__del(data, self.root)
            return None
    
    def __del(self, data: int, root: Node | None) -> Node | None:
        if root is None:
            return None
        
        if root.data == data:
            if root.left_child is None and root.right_child is None:
                return None
            
            if root.left_child is None:
                return root.right_child
            
            if root.right_child is None:
                return root.left_child
            
            successor = self.__findMin(root.right_child)
            successor_data = successor.data
            root = self.__del(successor_data, root)
            root.data = successor_data
            return root
        
        parent_of_node_to_delete = self.__findParent(data, root)
        node_to_delete = self.__search(data, parent_of_node_to_delete)
        left = parent_of_node_to_delete.left_child
        right = parent_of_node_to_delete.right_child
        if left == node_to_delete:
            right = None
        else:
            left = None
        
        if node_to_delete.left_child is None and node_to_delete.right_child is None:
            if left is None:
                parent_of_node_to_delete.right_child = None
            else:
                parent_of_node_to_delete.left_child = None
            
            return root
        
        if node_to_delete.left_child is None:
            if left is None:
                parent_of_node_to_delete.right_child = node_to_delete.right_child
            else:
                parent_of_node_to_delete.left_child = node_to_delete.right_child
            
            return root
        
        
        if node_to_delete.right_child is None:
            if left is None:
                parent_of_node_to_delete.right_child = node_to_delete.left_child
            else:
                parent_of_node_to_delete.left_child = node_to_delete.left_child
            
            return root
        

        successor = self.__findMin(node_to_delete.right_child)
        successor_data = successor.data
        root = self.__del(successor_data, root)
        node_to_delete.data = successor_data
        return root
        

        
            
    
    def search(self, data: int) -> Node | None:
        return self.__search(data, self.root)
    
    def __search(self, data: int, root: Node | None) -> Node | None:
        if root is None:
            return None
        
        if root.data == data:
            return root
        
        if root.data < data:
            return self.__search(data, root.right_child)
        
        return self.__search(data, root.left_child)
    
    def findMin(self) -> Node | None:
        return self.__findMin(self.root)
    
    def __findMin(self, root: Node | None) -> Node | None:
        if root is None:
            return None
        
        if root.left_child is None:
            return root
        
        return self.__findMin(root.left_child)
    
    def findMax(self) -> Node | None:
        return self.__findMax(self.root)
    
    def __findMax(self, root: Node | None) -> Node | None:
        if root is None:
            return None
        
        if root.right_child is None:
            return root
        
        return self.__findMax(root.right_child)
    
    def inOrder(self) -> None:
        self.__inOrder(self.root)
    
    def __inOrder(self, root: Node | None) -> None:
        if root is None:
            return None
        
        self.__inOrder(root.left_child)
        print(root.data, end=' ')
        self.__inOrder(root.right_child)
        return None
    

    def preOrder(self) -> None:
        self.__preOrder(self.root)
    
    def __preOrder(self, root: Node | None) -> None:
        if root is None:
            return None
        
        print(root.data, end=' ')
        self.__preOrder(root.left_child)
        self.__preOrder(root.right_child)

    
    def postOrder(self) -> None:
        self.__postOrder(self.root)
    
    def __postOrder(self, root: Node | None) -> None:
        if root is None:
            return None
        
        self.__postOrder(root.left_child)
        self.__postOrder(root.right_child)
        print(root.data, end=' ')
    

    def height(self) -> int:
        return self.__height(self.root)
    
    def __height(self, root: Node | None) -> int:
        if root is None:
            return 0
        
        if root.left_child is None and root.right_child is None:
            return 0
        
        if root.left_child is None:
            return 1 + self.__height(root.right_child)
        
        if root.right_child is None:
            return 1 + self.__height(root.left_child)
        
        height_left = self.__height(root.left_child)
        height_right = self.__height(root.right_child)

        return 1 + max(height_left, height_right)
    

    def size(self) -> int:
        return self.__size(self.root)
    
    def __size(self, root: Node | None) -> int:
        if root is None:
            return 0
        
        return 1 + self.__size(root.left_child) + self.__size(root.right_child)
    
    
    def validateBST(self) -> bool:
        if self.root is None:
            return True
        
        return self.__isBST(self.root, float('-inf'), float('inf'))
    
    def __isBST(self, root: Node | None, min_value: int, max_value: int) -> bool:
        if root is None:
            return True
        
        if root.data < min_value or root.data > max_value:
            return False
        
        return (self.__isBST(root.left_child, min_value, root.data) and
                self.__isBST(root.right_child, root.data, max_value))
    
    def findSuccessor(self, data: int) -> Node | None:
        return self.__findSuccessor(data, self.root)
    
    def __findSuccessor(self, data: int, root: Node | None) -> Node | None:
        if root is None:
            return None
        
        if root.data > data:
            left_successor = self.__findSuccessor(data, root.left_child)
            return left_successor if left_successor is not None else root
        else:
            return self.__findSuccessor(data, root.right_child)
    

    def findPredecessor(self, data: int) -> Node | None:
        return self.__findPredecessor(data, self.root)
    

    def __findPredecessor(self, data: int, root: Node | None) -> Node | None:
        if root is None:
            return None
        
        if root.data < data:
            right_predecessor = self.__findPredecessor(data, root.right_child)
            return right_predecessor if right_predecessor is not None else root
        else:
            return self.__findPredecessor(data, root.left_child)
    

    def countLeaves(self) -> int:
        return self.__countLeaves(self.root)
    

    def __countLeaves(self, root: Node | None) -> int:
        if root is None:
            return 0
        
        if root.left_child is None and root.right_child is None:
            return 1
        
        return self.__countLeaves(root.left_child) + self.__countLeaves(root.right_child)
    

    def isBalanced(self) -> bool:
        return self.__isBalanced(self.root)
    
    def __isBalanced(self, root: Node | None) -> bool:
        if root is None:
            return True
        
        balanced_left = self.__isBalanced(root.left_child)
        balanced_right = self.__isBalanced(root.right_child)
        height_left = self.__height(root.left_child)
        height_right = self.__height(root.right_child)
        balanced_root = (abs(height_left - height_right) <= 1)

        return (balanced_left and balanced_right and balanced_root)
    

    

    

    
        

        
        
        
       
        
       
