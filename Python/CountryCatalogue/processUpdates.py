from country import Country
from catalogue import CountryCatalogue

def processUpdates(cntryFileName,updateFileName,badUpdateFile):


    file = open(cntryFileName, "r")
    output = open("output.txt", "w")
    badupdates = open(badUpdateFile, "w")

    if file == None:

        while True:
            choice = input("Do you want to quit? 'Y' (yes) or 'N' (no): ")

            if choice.lower() == "n":
                fname = input("Enter name of file with country data: ")
                newfile = open(fname, "r")

                if newfile != None:
                    file = newfile
                    cntryFileName = fname
                    break


            elif choice.lower() != "n":

                output.write("Update Unsuccessful\n")
                output.close()
                return False, None


    print(cntryFileName)
    country = CountryCatalogue(cntryFileName)
    updatefile = open(updateFileName,"r")

    for line in updatefile:
        #line = line.strip()
        line = line.replace(' ','')

        info = line.split(";")

        country1 = Country(info[0], '', '', '')
        object = country.findCountry(country1)
        Pop = ""
        Continent = "North_America"
        Area = ""

        if object != None:

            Pop = object.getPopulation()
            Area = object.getArea()
            Continent = object.getContinent()

        if info[0] == "" or not info[0].isalpha():
            badupdates.write(line + "\n")
            continue


        fail = False
        p = False
        a = False
        c = False
        for elem in info[1:]:

            #elem = elem.strip()

            elem = elem.replace(' ','')
            print(elem, "hi")


            if elem[0] == 'P':
                if p:
                    badupdates.write(line + "\n")
                    fail = True
                    break
                p = True
                count = 0
                Pop = elem[2:]
                for i in range(len(Pop) - 1, -1, -1):
                    count += 1
                    if count % 4 == 0:
                        if Pop[i] != ',':
                            badupdates.write(line + "\n")
                            fail = True
                            print(Pop[i], "hello")
                            break

                    else:
                        if not Pop[i].isnumeric():
                            badupdates.write(line + "\n")
                            fail = True
                            print(Pop[i], "hello")
                            break


            elif elem[0] == 'A':
                if a:
                    badupdates.write(line + "\n")
                    fail = True
                    break
                a = True

                Area = elem[2:]
                count = 0
                for i in range(len(Area) - 1, -1, -1):
                    count += 1
                    if count % 4 == 0:
                        if Area[i] != ',':
                            badupdates.write(line + "\n")
                            fail = True
                            break
                    else:
                        if not Area[i].isnumeric():
                            badupdates.write(line + "\n")
                            fail = True
                            break

            elif elem[0] == 'C':
                if c:
                    badupdates.write(line + "\n")
                    fail = True
                    break
                c = True
                valid_names = ["Africa", "Antarctica", "Arctic", "Asia", "Europe", "North_America", "South_America"]

                Continent = elem[2:]
                if Continent not in valid_names:
                    badupdates.write(line + "\n")
                    fail = True
                    break
            else:
                badupdates.write(line + "\n")
                fail = True
                break

        if not fail:

            if object == None:
                country.addCountry(country1.getName(), Pop, Area, Continent)
            else:
                country.setPopulationOfCountry(country1, Pop)
                country.setAreaOfCountry(country1, Area)
                country.setContinentOfCountry(country1, Continent)


        file.close()

    country.saveCountryCatalogue("output.txt")

    return True, country


















