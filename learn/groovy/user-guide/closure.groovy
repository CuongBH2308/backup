def stringList = [ "java", "perl", "python", "ruby", "c#", "cobol",
                   "groovy", "jython", "smalltalk", "prolog", "m", "yacc" ]
                   
stringList.each() {println " ${it}"}
stringList.each {println " ${it}"}



def stringMap = [ "Su" : "Sunday", "Mo" : "Monday", "Tu" : "Tuesday",
                  "We" : "Wednesday", "Th" : "Thursday", "Fr" : "Friday",
                  "Sa" : "Saturday" ];
stringMap.each {key, value -> println "${key} = ${value}"}

stringMap.eachWithIndex {obj, i -> println "${i}: ${obj}" }