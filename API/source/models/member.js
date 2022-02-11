const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const MemberSchema = new Schema({
    id: String,
    name: String
});

module.exports = mongoose.model('Member', MemberSchema);