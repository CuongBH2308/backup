// expression:
// statement:

def (a1, b1) = [1, 2]
println a1+b1

def geocode(String location) {
    [48.8234, 2.532342]
}

def (_lat, _long) = geocode("Paris France")

print _lat


def (int i, String s) = [1, "Groovy"]


def elements = [1, 2]
def (a, b, c) = elements