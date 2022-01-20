import sys

class LetterStatistics():
    
    
    @staticmethod
    def analyze(filename, excludedCharacters, case_sensitive):
        LetterDict = {}
        filename = filename.split('.')[0] + ".txt"
        f = open(filename, 'r')
        for line in f.readlines():
            for c in line:
                if c in excludedCharacters:
                    continue
                if not case_sensitive:
                    c = c.lower()
                if c in LetterDict:
                    LetterDict[c] += 1
                else:
                    LetterDict[c] = 1
        f.close()
        return LetterDict




if __name__ == "__main__":
    outputStatistics = LetterStatistics.analyze(sys.argv[1],
                             " \n1234567890!@#$%^&*()_-=+~<>()[]{},.;:'\"\\/|?",
                             False)
    outputFile = open("ex2-output.txt", 'w')
    for c in outputStatistics:
        print("Letter: {0} count = {1}".format(c, outputStatistics[c]))
        outputFile.write("Letter: {0} count = {1}\n".format(c, outputStatistics[c]))
    outputFile.close()
