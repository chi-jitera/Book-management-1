const mongoose = require('../config/db');

module.exports = {
    up: async () => {
        await mongoose.connection.db.createCollection('tests', {
            validator: {
                $jsonSchema: {
                    bsonType: "object",
                    required: ["id", "created_at", "updated_at"],
                    properties: {
                        id: {
                            bsonType: "int",
                            description: "must be an integer and is required"
                        },
                        created_at: {
                            bsonType: "date",
                            description: "must be a date and is required"
                        },
                        updated_at: {
                            bsonType: "date",
                            description: "must be a date and is required"
                        }
                    }
                }
            }
        });
    },
    down: async () => {
        await mongoose.connection.db.dropCollection('tests');
    }
};