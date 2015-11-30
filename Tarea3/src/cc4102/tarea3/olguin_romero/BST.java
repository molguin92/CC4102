package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 29-11-15.
 */
public class BST implements  Tree{

    private BSTNode root;
    private int size;

    public BST()
    {
        this.root = null;
        this.size = 0;
    }

    @Override
    public void put(String key, String value) {
        if (this.root == null)
        {
            this.root = new BSTNode(key, value);
            size++;
        }
        else
        {
            if(root.put(key, value))
                size++;
        }
    }

    @Override
    public String get(String key) {
        if(root == null)
            return null;

        return root.get(key);
    }

    @Override
    public String delete(String key)
    {
        return null;
    }

    @Override
    public int size() {
        return this.size;
    }

    private class BSTNode implements Node
    {
        public BSTNode left;
        public BSTNode right;
        public String value;
        public String key;

        public BSTNode(String key, String value)
        {
            this.key = key;
            this.value = value;
            this.left = null;
            this.right = null;
        }

        /**
         * Adds a key-value pair to this node or one of its subtrees.
         * Returns a boolean variable indicating if a new node had to be added to the tree.
         * If the key already exists in the tree, updates the value.
         * @param key key
         * @param value value
         * @return true if a new leaf was added to the tree, false otherwise
         */
        @Override
        public boolean put(String key, String value) {
            int comp = key.compareTo(this.key);
            switch (comp) {
                case 0: // keys match, update value
                    this.value = value;
                    return false;
                case 1: // key > this key, insert into right subtree
                    if (this.right == null)
                    {
                        this.right = new BSTNode(key, value);
                        return true;
                    }

                    return this.right.put(key, value);

                case -1: // key < this key, insert into left subtree
                    if (this.left == null)
                    {
                        this.left = new BSTNode(key, value);
                        return true;
                    }

                    return this.left.put(key, value);

                default:
                    return false;
            }
        }

        /**
         * Finds the value associated with the supplied "key" parameter.
         * Returns null if the value is not found.
         * @param key key of the key-value pair.
         * @return value if key is present in the tree, null otherwise.
         */
        @Override
        public String get(String key) {
            int comp = key.compareTo(this.key);
            switch (comp)
            {
                case 0: // found the key, return value
                    return this.value;
                case 1: // key > this key, search in right subtree
                    if ( this.right == null )
                        return null;
                    return this.right.get(key);
                case -1: // key < this key, search in left subtree
                    if ( this.left == null )
                        return null;
                    return this.left.get(key);
                default:
                    return null;
            }
        }

        @Override
        public boolean delete(String key) {
            return false;
        }

        private BSTNode findLeftmost(BSTNode node)
        {
            BSTNode current = this;
            while(current.left != null)
                current = current.left;
            return current;
        }
    }
}
