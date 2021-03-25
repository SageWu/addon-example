(function callback() {
  const addon = require("./binding.js");
  addon.run(function(data) {
    console.log(data);
  })
})();