package cc4102.tarea3.olguin_romero;

public class AVLTree extends BinarySearchTree {

    public AVLTree() {
        super();
    }

    @Override
    public String get(int key)
    {
        return super.get(key);
    }

    @Override
    public void put(int key, String value) {
        if(root == null)
        {
            size++;
            root = new AVLNode(key, value);
        }
        else
        {
            root = root.put(key, value);
            root = recursive_rebalance((AVLNode) root);
        }
    }

    @Override
    public void delete(int key) {
        super.delete(key);
        root = recursive_rebalance((AVLNode) root);
    }

    private AVLNode rotateRight(AVLNode node)
    {
        /* rotate left child into parent position */
        AVLNode temp = (AVLNode) node.left;
        node.left = temp.right;
        temp.right = rebalance(node);
        temp = rebalance(temp);
        return temp;
    }

    private AVLNode rotateLeft(AVLNode node)
    {
        /* rotate right child into parent position */
        AVLNode temp = (AVLNode) node.right;
        node.right = temp.left;
        temp.left = rebalance(node);
        temp = rebalance(temp);
        return temp;
    }

    private AVLNode recursive_rebalance(AVLNode node)
    {
        if(node == null)
        {
            return null;
        }
        else {;
            node.left = recursive_rebalance((AVLNode) node.left);
            node.right = recursive_rebalance((AVLNode) node.right);
            return rebalance(node);
        }
    }

    private AVLNode rebalance(AVLNode node)
    {
        node.recalculateHeight();
        if (node.balance < -1) {
            // right > left
            if (((AVLNode) node.right).balance < 0)
                // right-right
                node = rotateLeft(node);
            else {
                //right-left
                node.right = rotateRight((AVLNode) node.right);
                node = rotateLeft(node);
            }
        } else if (node.balance > 1) {
            // left > right
            if (((AVLNode) node.left).balance > 0)
                // left-left
                node = rotateRight(node);
            else {
                //left-right
                node.left = rotateLeft((AVLNode) node.left);
                node = rotateRight(node);
            }
        }

        return node;
    }

    protected class AVLNode extends BSTNode
    {
        int height;
        int balance;

        AVLNode(int key, String value) {
            super(key, value);
            this.height = 0;
            this.balance = 0;
        }

        int recalculateHeight()
        {
            int hl = (this.left != null) ? ((AVLNode)this.left).height : -1;
            int hr = (this.right != null) ? ((AVLNode)this.right).height : -1;
            this.balance = hl - hr;
            this.height = Math.max(hl, hr) + 1;
            return this.height;
        }

        @Override
        public Node put(int key, String value) {
            if(this.key == key)
            {
                // found correct node
                this.value = value;
            }
            else if (key < this.key)
            {
                // put left
                if(this.left == null)
                {
                    size++;
                    this.left = new AVLNode(key, value);
                }
                else
                    this.left = this.left.put(key, value);
            }
            else
            {
                // put right
                if(this.right == null)
                {
                    size++;
                    this.right = new AVLNode(key, value);
                }
                else
                    this.right = this.right.put(key, value);
            }
            return this;
        }

        @Override
        Node popLeftmost(Node to_replace)
        {
            if(this.left != null)
            {
                this.left = ((AVLNode) this.left).popLeftmost(to_replace);
                return this;
            }
            else
            {
                // at the leftmost
                to_replace.key = this.key;
                to_replace.value = this.value;
                return this.right;
            }
        }

        @Override
        Node popRightmost(Node to_replace)
        {
            if(this.right != null)
            {
                this.right = ((AVLNode) this.right).popRightmost(to_replace);
                return this;
            }
            else
            {
                // at the leftmost
                to_replace.key = this.key;
                to_replace.value = this.value;
                return this.left;
            }
        }

        @Override
        Node replaceWithSuccessor()
        {
            Node ret;
            if(this.right.left == null)
            {
                // right child is the successor
                this.right.left = this.left;
                ret = this.right;
            }
            else
            {
                ret = ((AVLNode)this.right).popLeftmost(this);
            }
            return ret;
        }

        @Override
        Node replaceWithPredecessor()
        {
            Node ret;
            if(this.left.right == null)
            {
                // left child is the predecessor
                this.left.right = this.right;
                ret = this.left;
            }
            else
            {
                ret = ((AVLNode)this.left).popRightmost(this);
            }
            return ret;
        }

    }

}
