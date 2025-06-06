const Reader = require('../models/Reader');

exports.createReader = async (readerData) => {
    const reader = new Reader(readerData);
    return await reader.save();
};

exports.getReaderById = async (readerId) => {
    const reader = await Reader.findById(readerId);
    if (!reader) throw new Error('Reader not found');
    return reader;
};

exports.updateReader = async (readerId, updateData) => {
    const reader = await Reader.findByIdAndUpdate(readerId, updateData, { new: true, runValidators: true });
    if (!reader) throw new Error('Reader not found');
    return reader;
};

exports.deleteReader = async (readerId) => {
    const reader = await Reader.findByIdAndDelete(readerId);
    if (!reader) throw new Error('Reader not found');
    return { message: 'Reader deleted successfully' };
};
