package cc4102.tarea3.olguin_romero;

public class AVL extends BST{

    public AVL()
    {
        super();
    }

    @Override
    public void put(String key, String value) {
        if (this.root == null)
        {
            this.root = new BSTNode(key, value);
            size++;
        }
        else
            root = root.put(key, value);
    }


    protected class AVLNode extends BSTNode {

        public int height;
        public int balance;

        public AVLNode(String key, String value) {
            super(key, value);
            this.height = 0;
            this.balance = 0;
        }

        Node rotateLeft()
        {
            AVLNode node = (AVLNode) this.left;
            this.left = node.right;
            node.right = this;
            node.recalculateHeight();

            return node;
        }

        Node rotateRight()
        {
            AVLNode node = (AVLNode) this.right;
            this.right = node.left;
            node.left = this;
            node.recalculateHeight();

            return node;
        }

        void recalculateHeight()
        {
            int hl = (this.left != null) ? ((AVLNode)this.left).height : -1;
            int hr = (this.right != null) ? ((AVLNode)this.right).height: -1;
            this.height = Math.max(hl, hr) + 1;
            this.balance = hl - hr;
        }

        Node rebalance()
        {
            this.recalculateHeight(); // update height and balance
            if (this.balance < -1) // unbalanced to the right
            {
                if(((AVLNode)this.right).balance > 1) // right-left
                    this.right = ((AVLNode)this.right).rotateLeft();

                return this.rotateRight();
            }
            else if (this.balance > 1) // unbalanced to the left
            {
                if(((AVLNode)this.left).balance < -1) // left-right
                    this.left = ((AVLNode)this.left).rotateRight();

                return this.rotateLeft();
            }

            return this;
        }


        /**
         * Adds a key-value pair to this node or one of its subtrees.
         * If the key already exists in the tree, updates the value.
         * @param key key
         * @param value value
         */
        @Override
        public Node put(String key, String value) {
            int comp = key.compareTo(this.key);
            if (comp == 0) // keys match, update value
            {
                this.value = value;
                return this; // rebalancing is not necessary
            }
            else if (comp > 0) // key > this key, insert into right subtree
            {
                if (this.right == null)
                {
                    this.right = new AVLNode(key, value);
                    size++;
                }
                else
                    this.right = this.right.put(key, value);
            }
            else // key < this key, insert into left subtree
            {
                if (this.left == null)
                {
                    this.left = new AVLNode(key, value);
                    size++;
                }
                else
                    this.left = this.left.put(key, value);
            }

            return this.rebalance();
        }

        @Override
        public Node delete(String key) {
            return ((AVLNode)super.delete(key)).rebalance();
        }

        @Override
        protected Node replaceWithSuccessor()
        {
            Node[] rec_call = ((AVLNode)this.right).recursivePopSuccessorAndRebalance();
            rec_call[0].right = rec_call[1];
            rec_call[0].left = this.left;
            ((AVLNode)rec_call[0]).rebalance();
            return rec_call[0];
        }

        @Override
        protected Node replaceWithPredecessor()
        {
            Node[] rec_call = ((AVLNode)this.left).recursivePopPredecessorAndRebalance();
            rec_call[0].left = rec_call[1];
            rec_call[0].right = this.right;
            ((AVLNode)rec_call[0]).rebalance();
            return rec_call[0];
        }

        protected Node[] recursivePopSuccessorAndRebalance()
        {
            if(this.left == null) // at the successor
                return new Node[] {this, this.right};
            else
            {
                Node[] rec_call = ((AVLNode)this.left).recursivePopSuccessorAndRebalance();
                this.left = rec_call[1];
                this.rebalance();
                rec_call[1] = this;
                return rec_call;
            }
        }

        protected Node[] recursivePopPredecessorAndRebalance()
        {
            if(this.right == null) // at the predecessor
                return new Node[] {this, this.left};
            else
            {
                Node[] rec_call = ((AVLNode)this.right).recursivePopPredecessorAndRebalance();
                this.right = rec_call[1];
                this.rebalance();
                rec_call[1] = this;
                return rec_call;
            }
        }

    }

}
