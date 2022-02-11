const memberHandlers = require('./handlers/member')

module.exports = [
    {
        method: 'GET',
        path: '/api/v0/',
        handler: function (request, h) {
            return 'API Simple-TCS!';
        }
    },
    {
        method: 'GET',
        path: '/api/v0/member',
        handler: memberHandlers.getAll
    }
]