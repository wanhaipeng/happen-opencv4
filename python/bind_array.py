import sys, os
sys.path.insert(0, '../build/lib')
import bind_array
print(bind_array.__doc__)
import numpy as np
c = [1.0, 3.0]
a = np.array([[1,2],[3,4]], dtype=np.float32)
b = bind_array.ndarray_to_tensor(a,c)

d = bind_array.tensor_to_ndarray([1,2,3], [1.0, 2.0, 3.0, 4.0, 5.0, 6.0])
# print(d, d.shape)

a_dict = {'one': np.ones((1,2)), 'zero': np.zeros((1,2))}
bind_array.test_dict(a_dict)