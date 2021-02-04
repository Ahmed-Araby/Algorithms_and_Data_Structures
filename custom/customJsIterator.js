
/**
 * [] arodun the key 
 * is called computed  property names 
 * it just resolve the variable.
 */
var b = "name";
var obj = {
    a:1, 
    [b]:2, 
    // this one should return iterator.
    // this property is what defines iterable object in js 
    
    [Symbol.iterator]:function(){

        // build iterator on this object 
        let keys = Object.keys(this);
        let size = keys.length;
        let index = 0;
        return {
            next: ()=>{
                
                return (
                index < size ? 
                {done:false, value:this[keys[index++]]} :
                {done:true, value:undefined} ) 
            },

            rewind:()=>{
                index = 0;
                return;
            }
        }
    }
}

console.log("info ");
console.log("keys ",Object.keys(obj));
console.log(obj);
let it = obj[Symbol.iterator];
console.log("iteratir : ", it);

console.log("... dot on the object ", {...obj});
console.log("... dots on the object and the array ", [...obj]);
