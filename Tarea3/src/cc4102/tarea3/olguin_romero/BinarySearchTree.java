package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 29-11-15.
 */
public class BinarySearchTree implements Tree{

    Node root;
    int size;

    public BinarySearchTree()
    {
        root = null;
        size = 0;
    }

    @Override
    public void put(int key, String value) {
        if(root == null)
            root = new BSTNode(key, value);
        else
            root.put(key, value);
    }

    @Override
    public String get(int key) {
        if(root == null)
            return null;
        else
            return root.get(key);
    }

    @Override
    public void delete(int key) {

    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public Node getRoot() {
        return null;
    }

    protected class BSTNode extends Node
    {

        BSTNode(int key, String value)
        {
            this.key = key;
            this.value = value;
        }

        @Override
        Node put(int key, String value) {
            if(this.key == key)
            {
                // found correct node
                this.value = value;
            }
            else if (key < this.key)
            {
                // put left
                if(this.left == null)
                    this.left = new BSTNode(key, value);
                else
                    this.left = this.left.put(key, value);
            }
            else
            {
                // put right
                if(this.right == null)
                    this.right = new BSTNode(key, value);
                else
                    this.right = this.right.put(key, value);
            }
            return this;
        }

        @Override
        String get(int key) {
            if(this.key == key)
            {
                // found correct node
                return this.value;
            }
            else if (key < this.key)
            {
                // put left
                if(this.left == null)
                    return null;
                else
                    return this.left.get(key);
            }
            else
            {
                // put right
                if(this.right == null)
                    return null;
                else
                    return this.right.get(key);
            }
        }

        @Override
        Node delete(int key) {
            return null;
        }
    }
}
