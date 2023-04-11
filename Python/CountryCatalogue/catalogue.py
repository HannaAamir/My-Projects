from country import Country

class CountryCatalogue:
    def __init__(self, countryFile):

        self.countryCat = []

        file = open(countryFile, "r")
        header = file.readline()

        for line in file:
            line = line.strip()
            info = line.split("|")
            country_object = Country(info[0], info[2], info[3], info[1])
            self.countryCat.append(country_object)


        file.close()

    def setPopulationOfCountry(self, country, population):

        for i in range(len(self.countryCat)):
            if self.countryCat[i].getName() == country.getName():
                self.countryCat[i].setPopulation(population)

    def setAreaOfCountry(self, country, area):

        for i in range(len(self.countryCat)):
            if self.countryCat[i].getName() == country.getName():
                self.countryCat[i].setArea(area)

    def setContinentOfCountry(self, country, continent):

        for i in range(len(self.countryCat)):
            if self.countryCat[i].getName() == country.getName():
                self.countryCat[i].setContinent(continent)

    def findCountry(self, country):

        for country_object in self.countryCat:
            if country_object.getName() == country.getName():
                return country_object
        return None

    def addCountry(self, countryName, pop, area, cont):

        found = False
        for i in range(len(self.countryCat)):
            if self.countryCat[i].getName() == countryName:
                found = True
            if found:
                return False
            else:
                country_object = Country(countryName, pop, area, cont)
                self.countryCat.append(country_object)
                return True

    def printCountryCatalogue(self):

        for country_object in self.countryCat:
            print(repr(country_object))

    def saveCountryCatalogue(self, fname):

        count = 0

        for i in range(len(self.countryCat)):
            for j in range(i):
                if self.countryCat[i].getName() < self.countryCat[j].getName():
                    x = self.countryCat[i]
                    self.countryCat[i] = self.countryCat[j]
                    self.countryCat[j] = x

        file = open(fname, "w")
        file.write("Country|Continent|Population|Area\n")

        for country_object in self.countryCat:
            file.write(country_object.getName() + "|" + country_object.getContinent() + "|" + str(country_object.getPopulation()) + "|" + str(country_object.getArea()) + "\n")
            count += 1

        file.close()

        if count == len(self.countryCat):
            return count
        else:
            return -1

























