exports.up = function(knex) {
  return knex.schema.createTable('tests', function(table) {
    table.increments('id').primary();
    table.datetime('created_at').defaultTo(knex.fn.now());
    table.datetime('updated_at').defaultTo(knex.fn.now());
  });
};

exports.down = function(knex) {
  return knex.schema.dropTable('tests');
};