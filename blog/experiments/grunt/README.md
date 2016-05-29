* install node.js, which comes with npm (node packaged modules)
* grunt and grunt plugins are all managed by npm
* install grunt-cli: `npm install -g grunt-cli`
* use grunt to install dependencies for a local project - read from the package.json: `npm install` - it takes quite a while
* grunt has excellent docs: http://gruntjs.com/getting-started
* There are a lot of grunt [plugins](http://gruntjs.com/plugins) out there, and you can also [create your own plugin](http://gruntjs.com/creating-plugins)
* grunt build files:
   * Gruntfile - config the build with tasks
   * package.json - list grunt and grunt plugins as dev dependencies
* grunt terms:
   * task
   * target
   * options
   * src - dest mapping
* `grunt --help` to list all tasks of the project
* build bootstrap: http://getbootstrap.com/getting-started/
* grunt plugins use a lot of js/css/docs/sass/less toolings and testing frameworks ,which is very useful for web development