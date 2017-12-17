def start_platform(file):
    x =  "<?xml version='1.0'?>\n"
    x += "<!DOCTYPE platform SYSTEM \"http://simgrid.gforge.inria.fr/simgrid/simgrid.dtd\">\n"
    x += "<platform version=\"4.1\">\n"
    file.write(x)

def end_platform(file):
    x = "</platform>"
    file.write(x)


def actors(file):
    A = "\n"
    A += "\t<actor host=\"User\" function=\"user\"/>\n"
    A += "\t<actor host=\"Server1\" function=\"server1\"/>\n"
    A += "\t<actor host=\"Cache\" function=\"cache\"/>\n"
    A += "\t<actor host=\"SSD\" function=\"ssd\"/>\n"
    A += "\t<actor host=\"JBOD1\" function=\"jbod\"/>\n"
    A += "\t<actor host=\"JBOD2\" function=\"jbod\"/>\n"
    A += "\n"
    file.write(A)

if __name__ == '__main__':
    file = open("deployment.xml", "w")

    start_platform(file)
    actors(file)
    end_platform(file)