package cc4102.tarea3.olguin_romero;

import java.util.Random;

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
        {
            size++;
            root = new BSTNode(key, value);
        }
        else
            root = root.put(key, value);
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
        if(root != null)
            root = root.delete(key);
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public Node getRoot() {
        return root;
    }

    protected class BSTNode extends Node
    {

        BSTNode(int key, String value)
        {
            this.key = key;
            this.value = value;
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
                    this.left = new BSTNode(key, value);
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
                    this.right = new BSTNode(key, value);
                }
                else
                    this.right = this.right.put(key, value);
            }
            return this;
        }

        @Override
        public String get(int key) {
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
        public Node delete(int key) {
            if(this.key == key)
            {
                // delete myself
                size--;
                if(this.left == null && this.right == null) // no children
                {
                    return null;
                }
                else if (this.right == null) // left child
                {
                    return this.left;
                }
                else if (this.left == null) // right child
                {
                    return this.right;
                }
                else
                {
                    // both children. need to replace with successor or predecessor
                    int i = new Random().nextInt(2);
                    if(i == 0) {
                        return this.replaceWithPredecessor();
                    }
                    else {
                        return this.replaceWithSuccessor();
                    }
                }
            }
            else if (key < this.key)
            {
                if(this.left != null)
                    this.left = this.left.delete(key);
            }
            else
            {
                if(this.right != null)
                    this.right = this.right.delete(key);
            }
            return this;
        }

        Node popLeftmost(Node to_replace)
        {
            if(this.left != null)
            {
                this.left = ((BSTNode) this.left).popLeftmost(to_replace);
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

        Node popRightmost(Node to_replace)
        {
            if(this.right != null)
            {
                this.right = ((BSTNode) this.right).popRightmost(to_replace);
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
                ret = ((BSTNode)this.right).popLeftmost(this);
            }
            return ret;
        }

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
                ret = ((BSTNode)this.left).popRightmost(this);
            }
            return ret;
        }
    }
}
