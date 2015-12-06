package cc4102.tarea3.olguin_romero;

import java.util.Random;

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
            root.put(key, value);
    }

    @Override
    public String get(String key) {
        if(root == null)
            return null;

        return root.get(key);
    }

    @Override
    public void delete(String key)
    {
        if(root == null)
            return;

        root = (BSTNode)root.delete(key);
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
         * If the key already exists in the tree, updates the value.
         * @param key key
         * @param value value
         */
        @Override
        public void put(String key, String value) {
            int comp = key.compareTo(this.key);
            if (comp == 0) // keys match, update value
            {
                this.value = value;
            }
            else if (comp > 0) // key > this key, insert into right subtree
            {
                if (this.right == null)
                {
                    this.right = new BSTNode(key, value);
                    size++;
                    return;
                }

                this.right.put(key, value);
            }
            else // key < this key, insert into left subtree
            {
                if (this.left == null)
                {
                    this.left = new BSTNode(key, value);
                    size++;
                    return;
                }

                this.left.put(key, value);
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

            if (comp == 0) return this.value; // found the key, return value
            else if (comp > 0) { // key > this key, search in right subtree
                if (this.right == null)
                    return null;
                return this.right.get(key);
            }
            else // key < this key, search in left subtree
            {
                if ( this.left == null )
                    return null;
                return this.left.get(key);
            }
        }

        @Override
        public Node delete(String key) {
            int comp = key.compareTo(this.key);
            if (comp == 0)
            // found the key. need to delete ourselves
            // three cases = 0, 1, or 2 subtrees
            {
                size--;
                if (this.left == null && this.right == null) // no children
                    return null;
                else if (this.left == null) // just right child
                    return this.right;
                else if (this.right == null) // just left child
                    return this.left;
                else // both children
                {
                    int i = new Random().nextInt(2);
                    if ( i == 0 )
                        return this.replaceWithSuccessor();
                    else
                        return this.replaceWithPredecessor();
                }
            }
            else if ( comp > 0) // key > this key, search in right subtree
            {
                if ( this.right != null )
                    this.right = (BSTNode)this.right.delete(key);
            }
            else // key < this key, search in left subtree
            {
                if ( this.left != null )
                    this.left = (BSTNode)this.left.delete(key);
            }
            return this;
        }

        private BSTNode replaceWithSuccessor()
        {
            if(this.right.left == null){
                this.right.left = this.left;
                return this.right;
            }

            BSTNode parent = this.right;
            BSTNode current = this.right.left;
            while(current.left != null){
                parent = current;
                current = current.left;
            }
            parent.left = current.right;
            current.left = this.left;
            current.right = this.right;
            return  current;
        }

        private BSTNode replaceWithPredecessor()
        {
            if(this.left.right == null){
                this.left.right = this.right;
                return this.right;
            }

            BSTNode parent = this.left;
            BSTNode current = this.left.right;
            while(current.right != null){
                parent = current;
                current = current.right;
            }
            parent.right = current.left;
            current.right = this.right;
            current.left = this.left;
            return  current;
        }
    }
}
