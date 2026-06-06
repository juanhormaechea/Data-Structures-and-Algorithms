class AVLNode:
    def __init__(self, data: int):
        self.data = data
        self.left_child: AVLNode | None = None
        self.right_child: AVLNode | None = None
        self.height = 0


class AVLT:
    def __init__(self):
        self.root: AVLNode | None = None
    
    def __getHeight(self, node: AVLNode | None) -> int:
        return -1 if node is None else node.height
    
    
    def __updateHeight(self, node: AVLNode) -> None:
        hl = self.__getHeight(node.left_child)
        hr = self.__getHeight(node.right_child)
        node.height = 1 + (hl if hl >= hr else hr)
        return None
    

    def __getBalanceFactor(self, node: AVLNode) -> int:
        return (self.__getHeight(node.left_child) - self.__getHeight(node.right_child))
    

    def __rotateRight(self, y: AVLNode) -> AVLNode:
        x_left = y.left_child
        y.left_child = x_left.right_child
        x_left.right_child = y

        self.__updateHeight(y)
        self.__updateHeight(x_left)
        return x_left
    

    def __rotateLeft(self, x: AVLNode) -> AVLNode:
        y_right = x.right_child
        x.right_child = y_right.left_child
        y_right.left_child = x

        self.__updateHeight(x)
        self.__updateHeight(y_right)
        return y_right
    
    
    def __rebalance(self, unbalanced_node: AVLNode) -> AVLNode:
        current_balance_factor = self.__getBalanceFactor(unbalanced_node)
        balanced_node = None
        if current_balance_factor == 2:
            balance_factor_left = self.__getBalanceFactor(unbalanced_node.left_child)
            if balance_factor_left >= 0:
                balanced_node = self.__rotateRight(unbalanced_node)
            else:
                unbalanced_node.left_child = self.__rotateLeft(unbalanced_node.left_child)
                balanced_node = self.__rotateRight(unbalanced_node)
        elif current_balance_factor == -2:
            balance_factor_right = self.__getBalanceFactor(unbalanced_node.right_child)
            if balance_factor_right <= 0:
                balanced_node = self.__rotateLeft(unbalanced_node)
            else:
                unbalanced_node.right_child = self.__rotateRight(unbalanced_node.right_child)
                balanced_node = self.__rotateLeft(unbalanced_node)
        else:
            balanced_node = unbalanced_node
        
        return balanced_node
    
    def __insert(self, root: AVLNode | None, data: int) -> AVLNode:
        if root is None:
            return AVLNode(data)
        
        if root.data == data:
            return root
        
        if root.data < data:
            root.right_child = self.__insert(root.right_child, data)
        else:
            root.left_child = self.__insert(root.left_child, data)
        
        self.__updateHeight(root)
        return self.__rebalance(root)
    
    def insert(self, data: int) -> None:
        self.root = self.__insert(self.root, data)

    

    def __del(self, root: AVLNode | None, data: int) -> AVLNode | None:
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
            assert successor is not None # For type checkers
            successor_data = successor.data
            root.data = successor_data
            root.right_child = self.__del(root.right_child, successor_data)
            self.__updateHeight(root)
            return self.__rebalance(root)
        

        if root.data < data:
            root.right_child = self.__del(root.right_child, data)
            self.__updateHeight(root)
            return self.__rebalance(root)
        
        root.left_child = self.__del(root.left_child, data)
        self.__updateHeight(root)
        return self.__rebalance(root)
    


    def delete(self, data: int) -> None:
        self.root = self.__del(self.root, data)
        return None
    
    

    def __search(self, root: AVLNode | None, data: int) -> AVLNode | None:
        if root is None:
            return None
        
        if root.data == data:
            return root
        
        if root.data < data:
            return self.__search(root.right_child, data)
        
        return self.__search(root.left_child, data)
    

    def search(self, data: int) -> AVLNode | None:
        return self.__search(self.root, data)
    

    def __findMin(self, root: AVLNode | None) -> AVLNode | None:
        if root is None:
            return None
        
        if root.left_child is None:
            return root
        
        return self.__findMin(root.left_child)
    

    def findMin(self) -> AVLNode | None:
        return self.__findMin(self.root)
    

    def __findMax(self, root: AVLNode | None) -> AVLNode | None:
        if root is None:
            return None
        
        if root.right_child is None:
            return root
        
        return self.__findMax(root.right_child)
    

    def findMax(self) -> AVLNode | None:
        return self.__findMax(self.root)
    


    def __inOrder(self, root: AVLNode | None) -> None:
        if root is None:
            return None
        self.__inOrder(root.left_child)
        print(root.data, end=" ")
        
        self.__inOrder(root.right_child)
        return None


    def inOrder(self) -> None:
        self.__inOrder(self.root)
    

    
    def __preOrder(self, root: AVLNode | None) -> None:
        if root is None:
            return None
        print(root.data, end=" ")
        self.__preOrder(root.left_child)
        self.__preOrder(root.right_child)
        return None
    
    def preOrder(self) -> None:
        self.__preOrder(self.root)
    


    def __postOrder(self, root: AVLNode | None) -> None:
        if root is None:
            return None
        
        self.__postOrder(root.left_child)
        self.__postOrder(root.right_child)
        print(root.data, end=" ")
        return None
    
    
    def postOrder(self) -> None:
        self.__postOrder(self.root)

    

    def height(self) -> int:
        return 0 if self.root is None else self.root.height
    

    def __size(self, root: AVLNode | None) -> int:
        if root is None:
            return 0
        
        return 1 + self.__size(root.right_child) + self.__size(root.left_child)
    
    def size(self) -> int:
        return self.__size(self.root)
    


    def isEmpty(self) -> bool:
        return (self.__size(self.root) == 0)
    

    def __isAVL(self, root: AVLNode | None, min_val: float = float('-inf'), max_val: float = float('inf')) -> bool:
        if root is None:
            return True
        
        height_left = self.__getHeight(root.left_child)
        height_right = self.__getHeight(root.right_child)
        expected_height = 1 + (height_left if height_left >= height_right else height_right)

        if root.data <= min_val or root.data >= max_val or abs(height_left - height_right) > 1 or root.height != expected_height:
            return False
        
        return (self.__isAVL(root.left_child, min_val, root.data) and self.__isAVL(root.right_child, root.data, max_val))
    

    def validateAVL(self) -> bool:
        return self.__isAVL(self.root)
    


    def __findSuccessor(self, root: AVLNode | None, data: int) -> AVLNode | None:
        if root is None:
            return None
        
        if root.data > data:
            possible_successor = self.__findSuccessor(root.left_child, data)
            return (possible_successor if possible_successor is not None else root)

        
        return self.__findSuccessor(root.right_child, data)
    

    def findSuccessor(self, data: int) -> AVLNode | None:
        return self.__findSuccessor(self.root, data)
    

    def __findPredecessor(self, root: AVLNode | None, data: int) -> AVLNode | None:
        if root is None:
            return None
        
        if root.data < data:
            possible_predecessor = self.__findPredecessor(root.right_child, data)
            return (possible_predecessor if possible_predecessor is not None else root)
        

        return self.__findPredecessor(root.left_child, data)
    

    def findPredecessor(self, data: int) -> AVLNode | None:
        return self.__findPredecessor(self.root, data)
    


    def __countLeaves(self, root: AVLNode | None) -> int:
        if root is None:
            return 0
        
        if root.left_child is None and root.right_child is None:
            return 1
        
        return self.__countLeaves(root.left_child) + self.__countLeaves(root.right_child)
    

    def countLeaves(self) -> int:
        return self.__countLeaves(self.root)
    





    
