class node
{
    constructor(value)
    {
        this.value = value; // abstruct data type
        this.height = 0;
        this.balanceFactor = 0;
        this.leftPtr = null;
        this.rightPtr = null;
        return ;
    }
}

class AVLTree
{
    constructor(compare_function)
    {
        /*
        comparison function 
        will take value as first argument 
        and root.value as second argument 
        
        return 
        -1 for value < root.value 
        0 for equality 
        1 for value > root.value
        */
        
        this.compare_function = compare_function;
        
        this.root = null;
        this.minValuePtr = null;
        this.maxValuePtr = null;
        this.size = 0;
        return ;        
    }
    
    length()
    {
        return this.size;
    }
    
    min_value()
    {
        // return value of the min value in the tree 
        
        return this.minValuePtr.value;
    }
    
    max_value()
    {
        // return the value of the max value in the tree 
        
        return this.maxValuePtr.value;
    }
    
    // work on it as if was a normal binary search tree 
    
    _contains(value, root)
    {
        if(root==null)
            return false;
        var comparison_result = this.compare_function(value, root.value);
        if(comparison_result == 0)
            return true;
        else if(comparison_result == 1)
            return this._contains(value, root.rightPtr);
        else 
            return this._contains(value, root.leftPtr);      
    }
    
    contains(value)
    {
        return this._contains(value, this.root);
    }
        
    _insert(value, root)
    {
        // keep track of min and max value 
        if(root==null){
            root = new node(value);
            
            if(this.minValuePtr==null ||
               this.compare_function(value, this.minValuePtr.value) == -1)
                this.minValuePtr = root;
            
            if(this.maxValuePtr==null || 
               this.compare_function(value, this.maxValuePtr.value) == 1)
                this.maxValuePtr = root;
            
            return root;
        }
        
        var comparison_result = this.compare_function(value, root.value);
        
        if(comparison_result==1)
            root.rightPtr = this._insert(value, root.rightPtr);
        else 
            root.leftPtr = this._insert(value, root.leftPtr);
        
        // force the tree to be balanced bst 
        this._update(root);
        root = this._balance(root);
        // end
        
        return root;
    }
    
    insert(value)
    {
        
        if(this.contains(value))
        {
            return false;
        }
        
        else{
            this.root = this._insert(value, this.root);
            this.size +=1;
            return true;
        }
    }
    
    _remove(value, root, parent)
    {
        /*
        - value to be removed 
        - root of the current subtree 
        - parent of the current subtree to keep track of the 
            max and min value in case that we delete one of them
            as it's dad will next one with such property.
        */
        
        // base case 
        var comparison_result = this.compare_function(value, root.value);
        if(comparison_result == 0)
        {
            comparison_result = this.compare_function(root.value, this.minValuePtr.value);
            
            // keep track of min and max  value
            if(comparison_result == 0)
            {
                if(root.leftPtr==null && root.rightPtr==null)
                    this.minValuePtr = parent;
                else if(root.rightPtr!=null && root.leftPtr==null)
                    this.minValuePtr = this._get_min(root.rightPtr);
            }
            
            comparison_result = this.compare_function(root.value, this.maxValuePtr.value);
            
            if(comparison_result == 0)
            {
                if(root.leftPtr==null && root.rightPtr==null)
                    this.maxValuePtr = parent;
                else if(root.rightPtr==null && root.leftPtr!=null)
                    this.maxValuePtr = this._get_max(root.leftPtr);
            }
            
            // stop cases 
            if(root.leftPtr==null)
            {
                return root.rightPtr;
            }
            else if(root.rightPtr==null)
            {
                return root.leftPtr;
            }
            
            else{
                
                /*
                get max from left subtree 
                or 
                get min from right subtree
                and this will be a leaf node
                or node with 1 child 
                so it will hit one of the upper conditions
                */
                
                var maxValuePtr = this._get_max(root.leftPtr);
                var maxValue = maxValuePtr.value;
                
                root.leftPtr = this._remove(maxValue, root.leftPtr, root);
                root.value = maxValue;
                
                /*
                need update and balance
                will happen bellow 
                */
            }
        }
        
        else if(comparison_result == 1)
            root.rightPtr = this._remove(value, root.rightPtr, root);
        else 
            root.leftPtr = this._remove(value, root.leftPtr, root);
        
        // force the tree to be balanced bst 
        this._update(root);
        root = this._balance(root);
        // end
        
        return root;
    }
    
    _get_max(root)
    {   
        /*
        return reference to the max value 
        in a specific subtree
        */
        
        if(root.rightPtr == null)
            return root;
        return this._get_max(root.rightPtr);
        
    }
    _get_min(root)
    {
        /*
        return reference to the min value 
        in a specific subtree
        */
        
        if(root.leftPtr==null)
            return root;
        return this._get_min(root.leftPtr)
    }
    
    remove(value)
    {
        if(this.size == 0 || !this.contains(value))
        {
            return false;
        }
        
        else{
            this.root = this._remove(value, this.root, null);
            this.size-=1;
            if(this.minValuePtr==null)
                this.minValuePtr = this.maxValuePtr;
            else if(this.maxValuePtr==null)
                this.maxValuePtr = this.minValuePtr;
            
            return true;
        }
    }
    
    pop()
    {
        // remove minimum value in the tree
        return this.remove(this.min_value());
    }
    
    _before(value, root, lastSmallerNode)
    {
        if(root==null)
            return null;
        
        var comparison_result = this.compare_function(value, root.value);
        if(comparison_result == 0)
        {
            if(root.leftPtr!=null)
                return this._get_max(root.leftPtr);
            return lastSmallerNode;
        }
        else if(comparison_result == -1)
            return this._before(value , root.leftPtr, lastSmallerNode);
        else 
            return this._before(value, root.rightPtr, root);
    }
    
    before(value)
    {
        return this._before(value, this.root, null);
    }
    
    _after(value, root, lastBiggerNode)
    {
        if(root==null)
            return null;
        var comparison_result = this.compare_function(value, root.value);
        if(comparison_result == 0)
        {
            if(root.rightPtr!=null)
                return this._get_min(root.rightPtr);
            return lastBiggerNode;
        }
        else if(comparison_result == -1)
            return this._after(value, root.leftPtr, root);
        else 
            return this._after(value, root.rightPtr, lastBiggerNode);
    }
    
    after(value)
    {
        return this._after(value, this.root, null);
    }
    
    
    /*
    balanced binary search tree section
    */
    _left_rotation(root)
    {
        var rightPtr = root.rightPtr;
        root.rightPtr = rightPtr.leftPtr;        
        rightPtr.leftPtr = root;
        
        // order matters
        this._update(root);
        this._update(rightPtr);
        
        return rightPtr;
    }
    
    _right_rotation(root)
    {
        var leftPtr = root.leftPtr;
        root.leftPtr = leftPtr.rightPtr;
        leftPtr.rightPtr = root;
        
        // order metters
        this._update(root);
        this._update(leftPtr);
        
        return leftPtr;
    }
    
    _balance(root)
    {
        var balanceFactor = root.balanceFactor;
        if(balanceFactor>=-1 && balanceFactor<=1)
            return root;
        var newRoot = null;
        
        if(balanceFactor==-2){
            var rightBalanceFactor = root.rightPtr.balanceFactor;
            if(rightBalanceFactor>0)
                // right rotation for the lowe par t
                root.rightPtr = this._right_rotation(root.rightPtr);
                            
            // left rotation for the root
            newRoot = this._left_rotation(root);
            
        }
        else if(balanceFactor==2)
        {
            var leftBalanceFactor = root.leftPtr.balanceFactor;
            if(leftBalanceFactor<0)
                // left rotation for the lower left part 
                root.leftPtr = this._left_rotation(root.leftPtr);
            
            // right rotation for the root 
            newRoot = this._right_rotation(root);
        }
        return newRoot;
        
    }
    
    _update(root)
    {
        var leftHeight = 0 , rightHeight = 0;
        
        if(root.leftPtr!=null)
            leftHeight  =  1 + root.leftPtr.height;
        if(root.rightPtr!=null)
            rightHeight =  1 + root.rightPtr.height;
        root.height = Math.max(leftHeight, rightHeight);
        root.balanceFactor = leftHeight-rightHeight;
        return ;
    }
    
     
    // for testing
    _dfs(root)
    {
        if(root==null)
            return ;
        console.log(root.value, root.height, root.balanceFactor);
        this._dfs(root.leftPtr);
        this._dfs(root.rightPtr);
        return ;
    }
    
    dfs()
    {
        this._dfs(this.root);
    }
}
