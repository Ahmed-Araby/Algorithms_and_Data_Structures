def z_function(s)
    n = s.length;
    arr = Array.new(n, 0);
    z = Array.new(n, 0);
    l = 0
    r = 0
    i = 0
    while i < n do
        if i <= r
            z[i] = [r-i+1, z[i-l]].min
        end

        while i+z[i] < n && s[z[i]] == s[i+z[i]] do
            z[i] +=1
        end

        if i+z[i] - 1 > r
            l = i 
            r = i + z[i] -1  
        end
        i+=1
    end
    return z
end

def count_occurance(s, z)
    n = s.length
    index = 0;
    cnt = z.reduce(0) do |cnt, val|
        if index <= n
            index +=1

        elsif val == n 
            cnt +=1
        end
        
        cnt;
        
    end
    
    return cnt;
end 

def match(text, pattern)
    s = pattern + "*" + text;
    z = z_function(s)
    cnt = count_occurance(pattern, z)
    return cnt;
end
