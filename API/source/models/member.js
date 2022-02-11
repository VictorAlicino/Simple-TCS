const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const MemberSchema = new Schema({
    firstName: String,
    lastName: String,
    RFID: String,
    lastTimeCheck: Date,
    isActive: Boolean
});

module.exports = mongoose.model('Member', MemberSchema);