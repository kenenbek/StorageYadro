
SSD_amount = 96
HDD_JBOD_amount = 128


def start_platform(file):
    x =  "<?xml version='1.0'?>\n"
    x += "<!DOCTYPE platform SYSTEM \"http://simgrid.gforge.inria.fr/simgrid/simgrid.dtd\">\n"
    x += "<platform version=\"4.1\">\n"
    x += "\t<zone id=\"AS0\" routing=\"Full\">"
    file.write(x)

def end_platform(file):
    x = "\t</zone>\n"
    x += "</platform>"
    file.write(x)


def storages_and_types(file):
    comment = "\t\t<!--HDD storage type -->\n"
    file.write("\n" + comment)
    x =  "\t\t<storage_type id=\"HDD\" size=\"12TB\">\n"
    x += "\t\t\t<model_prop id=\"Bread\" value=\"92MBps\"/>\n"
    x += "\t\t\t<model_prop id=\"Bwrite\" value=\"62MBps\"/>\n"
    x += "\t\t</storage_type>\n"
    file.write(x)

    comment = "\t\t<!--SDD storage type-->\n"
    file.write("\n" + comment)
    y =  "\t\t<storage_type id=\"SDD\" size=\"8TB\">\n"
    y += "\t\t\t<model_prop id=\"Bread\" value=\"920MBps\"/>\n"
    y += "\t\t\t<model_prop id=\"Bwrite\" value=\"620MBps\"/>\n"
    y += "\t\t</storage_type>\n"
    file.write(y)

    comment = "\t\t<!--Cache storage type-->\n"
    file.write("\n" + comment)
    z =  "\t\t<storage_type id=\"Cache\" size=\"256GB\">\n"
    z += "\t\t\t<model_prop id=\"Bread\" value=\"9200MBps\"/>\n"
    z += "\t\t\t<model_prop id=\"Bwrite\" value=\"6200MBps\"/>\n"
    z += "\t\t</storage_type>\n"
    file.write(z)

    comment = "\t\t<!--CACHE array-->\n"
    file.write("\n" + comment)
    for i in range(1):
        Cache =  "\t\t<storage id=\"Cache_" +str(i) + "\" typeId=\"Cache\" attach=\"" + "Cache" + "\"/>\n"
        # Cache += "\t\t</storage>\n"
        file.write(Cache)

    comment = "\t\t<!--SSD array-->\n"
    file.write("\n" + comment)
    for i in range(SSD_amount):
        SSD =  "\t\t<storage id=\"SSD_" +str(i) + "\" typeId=\"SDD\" attach=\"" + "SSD" + "\"/>\n"
        # SSD += "\t\t</storage>\n"
        file.write(SSD)


    comment = "\t\t<!--HDD JBOD1 array-->\n"
    file.write("\n" + comment)
    for i in range(HDD_JBOD_amount):
        HDD =  "\t\t<storage id=\"JBOD1HDD_" +str(i) + "\" typeId=\"HDD\" attach=\"" + "JBOD1" + "\"/>\n"
        # HDD += "\t\t</storage>\n"
        file.write(HDD)


    comment = "\t\t<!--HDD JBOD2 array-->\n"
    file.write("\n" + comment)
    for i in range(HDD_JBOD_amount):
        HDD =  "\t\t<storage id=\"JBOD2HDD_" +str(i) + "\" typeId=\"HDD\" attach=\"" + "JBOD2" + "\"/>\n"
        # HDD += "\t\t</storage>\n"
        file.write(HDD)



def hosts(file):
    comment = "\t\t<!--Servers array-->\n"
    file.write("\n" + comment)

    A0 =  "\t\t<host id=\"User\" speed=\"1Gf\">\n"
    A0 += "\t\t</host>\n"
    file.write(A0)

    A =  "\t\t<host id=\"Server1\" speed=\"1Gf\">\n"
    A += "\t\t</host>\n"
    file.write(A)

    comment = "\t\t<!--Cache server array-->\n"
    file.write("\n" + comment)
    B =  "\t\t<host id=\"Cache\" speed=\"1Gf\">\n"
    B += "\t\t\t<mount storageId=\"Cache\" name=\"/Cache\"/>\n"
    B += "\t\t</host>\n"
    file.write(B)

    comment = "\t\t<!--SSD server array-->\n"
    file.write("\n" + comment)
    C =  "\t\t<host id=\"SSD\" speed=\"1Gf\">\n"
    for i in range(SSD_amount):
        C += "\t\t\t<mount storageId=\"SSD" + str(i) +"\" name=\"/SSD" + str(i) + "\"/>\n"
    C += "\t\t</host>\n"
    file.write(C)

    comment = "\t\t<!--JBOD1 server array-->\n"
    file.write("\n" + comment)
    D =  "\t\t<host id=\"JBOD1\" speed=\"1Gf\">\n"
    for i in range(HDD_JBOD_amount):
        D += "\t\t\t<mount storageId=\"JBOD1HDD_" + str(i) +"\" name=\"/JBOD1HDD_" + str(i) + "\"/>\n"
    D += "\t\t</host>\n"
    file.write(D)

    comment = "\t\t<!--JBOD2 server array-->\n"
    file.write("\n" + comment)
    E =  "\t\t<host id=\"JBOD2\" speed=\"1Gf\">\n"
    for i in range(HDD_JBOD_amount):
        E += "\t\t\t<mount storageId=\"JBOD2HDD_" + str(i) +"\" name=\"/JBOD2HDD_" + str(i) + "\"/>\n"
    E += "\t\t</host>\n"
    file.write(E)

def links(file):
    comment = "\t\t<!--LINKS-->\n"
    file.write("\n" + comment)
    L = "\t\t<link id=\"User_Server1\" bandwidth=\"10GBps\" latency=\"50us\"/>\n"
    L += "\t\t<link id=\"Server1_Cache\" bandwidth=\"64GBps\" latency=\"50us\"/>\n"
    L += "\t\t<link id=\"Cache_SSD\" bandwidth=\"64GBps\" latency=\"50us\"/>\n"
    L += "\t\t<link id=\"Cache_JBOD1\" bandwidth=\"64GBps\" latency=\"50us\"/>\n"
    L += "\t\t<link id=\"Cache_JBOD2\" bandwidth=\"64GBps\" latency=\"50us\"/>\n"
    file.write(L)

def routes(file):
    comment = "\t\t<!--ROUTES-->\n"
    file.write("\n" + comment)

    R = "\t\t<route src=\"User\" dst=\"Server1\">\n"
    R += "\t\t\t<link_ctn id=\"User_Server1\"/>\n"
    R += "\t\t</route>\n"

    R += "\t\t<route src=\"Server1\" dst=\"Cache\">\n"
    R += "\t\t\t<link_ctn id=\"Server1_Cache\"/>\n"
    R += "\t\t</route>\n"

    R += "\t\t<route src=\"Cache\" dst=\"SSD\">\n"
    R += "\t\t\t<link_ctn id=\"Cache_SSD\"/>\n"
    R += "\t\t</route>\n"

    R += "\t\t<route src=\"Cache\" dst=\"JBOD1\">\n"
    R += "\t\t\t<link_ctn id=\"Cache_JBOD1\"/>\n"
    R += "\t\t</route>\n"

    R += "\t\t<route src=\"Cache\" dst=\"JBOD2\">\n"
    R += "\t\t\t<link_ctn id=\"Cache_JBOD2\"/>\n"
    R += "\t\t</route>\n"

    file.write(R)



if __name__ == '__main__':
    file = open('platform.xml', 'w')

    start_platform(file)
    storages_and_types(file)
    hosts(file)
    links(file)
    routes(file)
    end_platform(file)

    file.close()

