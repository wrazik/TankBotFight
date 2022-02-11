from cgi import test


def adding (x, y):
    return x + y

print(adding(2, 1))



def test_adding():
    assert adding(2, 2) == 4






