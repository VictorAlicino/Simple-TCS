const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const TimeCheckSchema = new Schema({
    memberId: ObjectId,
    date: Date,
    checkInTime: String,
    checkOutTime: String
});

module.exports = mongoose.model('TimeCheck', TimeCheckSchema);