const Reader = require('../models/Reader');

exports.createReader = async (readerData) => {
    const reader = new Reader(readerData);
    return await reader.save();
};

exports.getReaders = async () => {
    return await Reader.find();
};

exports.getReaderById = async (id) => {
    return await Reader.findById(id);
};

exports.updateReader = async (id, readerData) => {
    return await Reader.findByIdAndUpdate(id, readerData, { new: true });
};

exports.deleteReader = async (id) => {
    return await Reader.findByIdAndDelete(id);
};
