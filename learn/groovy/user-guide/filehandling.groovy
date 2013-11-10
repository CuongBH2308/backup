// read a file, print out matched pattern...
// file: current file
// pattern: function calls
scriptFile ="D:\\Source\\GitHub\\privaterepo\\learn\\groovy\\user-guide\\filehandling.groovy"


def data = []

new File(scriptFile).eachLine { 
    line -> data.add(line)
}

new File(scriptFile + '.backup').withWriter { out ->
    data.each() {
        out.writeLine(it)
        println it
    }
}