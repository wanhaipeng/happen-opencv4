import sys, os
sys.path.insert(0, '../build/lib')
import bind_array
print(bind_array.__doc__)
import numpy as np
c = [1.0, 3.0]
a = np.array([[1,2],[3,4]], dtype=np.float32)
b = bind_array.ndarray_to_tensor(a,c)

# bind_array.set_list(c)
print(c)

print(b)
print(a)
