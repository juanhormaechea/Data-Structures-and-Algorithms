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
    
    
