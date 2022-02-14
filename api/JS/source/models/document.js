const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const DocumentSchema = new Schema({
    memberId: ObjectId,
    type: String,
    institution: String,
    identifier: String
});

module.exports = mongoose.model('Document', DocumentSchema);