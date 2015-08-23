# How-Late
Pebble Time (Basalt) app integrating with Google Calendar API 


#### Contributing

> Fork this current repository

```sh
git clone https://github.com/[YOUR-GITHUB-USERNAME]/how-late.git
git remote add upstream https://github.com/irfansharif/how-late.git
git checkout -b my-new-feature
git commit -am 'Add some feature'
git push origin my-new-feature
```
> Create a new pull request


#### Compiling
> Download and install the latest SDK from http://developer.getpebble.com/sdk/

```sh
git clone https://github.com/irfansharif/how-late.git
cd how-late
pebble build && pebble install --emulator basalt
```

#### Debugging
> For debugging purposes add the following to any C & JavaScript code respectively

```C
APP_LOG(APP_LOG_LEVEL_INFO, "Hello, is it me you're looking for?");
```
```JavaScript
console.log('I can see it in your eyes')
```
> To view the logs during runtime in a separate terminal window execute

```sh
pebble logs --emulator basalt
```


