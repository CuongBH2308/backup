function addEventListeners(document) {
	var continueInput = true
	var numButtons = document.getElementsByClassName("number")
	console.log("number button count: " + numButtons.length)
	var outputField = document.getElementById("output")
	var i
	for (i = 0; i < numButtons.length; i++) {
		var elem = numButtons[i]
		console.log(elem)
		elem.addEventListener('click', function() {
			// you can't use elem here hope the closure works, use this
			// elem changes, so what you get is the last elem (0)
			console.log(this)
			if(continueInput) {
				outputField.value = outputField.value + this.value
			} else {
				outputField.value = this.value
				continueInput = true
			}
		})
	}

	var opButtons = document.getElementsByClassName("operator")
	console.log("operator button count: " + opButtons.length)
	for (i = 0; i < opButtons.length; i++) {
		var elem = opButtons[i]
		console.log(elem)
		elem.addEventListener('click', function() {
			// you can't use elem here hope the closure works, use this
			// elem changes, so what you get is the last elem (0)
			console.log(this)
			if(continueInput) {
				outputField.value = outputField.value + this.value
			} else {
				outputField.value = this.value
				continueInput = true
			}
		})
	}

	var executeButton = document.getElementById('execute')
	executeButton.addEventListener('click', function () {
		outputField.value = eval(outputField.value)
		continueInput = false
	})

	var clearButton = document.getElementById('clear')
	clearButton.addEventListener('click', function () {
		outputField.value = ""
	})
}


function on_number_click() {
	var output = document.getElementById("output")
	output.value = output.value + '1'
}

// write a website to convert templature
function toCelsius(fahrenheit) {
	return (5/9) * (fahrenheit-32);
} 