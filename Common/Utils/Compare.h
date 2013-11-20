//
//  Compare.h
//  Renderer
//
//  Created by Benjamin Gregorski on 11/15/13.
//
//

#ifndef Renderer_Compare_h
#define Renderer_Compare_h

namespace Framework { namespace Utils { namespace Compare {
 
    template <typename T>
    class LessThan {
        friend bool operator()(const T& a, const T& b) {
            return (a < b);
        }
    };
    
    template <typename T>
    class LessThanEqual {
        friend bool operator()(const T& a, const T& b) {
            return (a <= b);
        }
    };
    
    template <typename T, typename F>
    class Compare {
        friend bool operator()(const T& a, const T& b) {
            return F(a,b);
        }
    };
    
}
}
}

#endif
