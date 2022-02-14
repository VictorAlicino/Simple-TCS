const mongoose = require('mongoose');
mongoose.connect('mongodb://root:password@mongo:27017/simple_tcs?authSource=admin', {useNewUrlParser: true, useUnifiedTopology: true});