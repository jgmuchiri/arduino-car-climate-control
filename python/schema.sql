drop table if exists settings;
create table settings (
  id integer primary key autoincrement,
  option VARCHAR(20) not null,
  value VARCHAR(20) not null
);

INSERT into settings (option,value) VALUES ('fan_speed',300);
INSERT into settings (option,value) VALUES ('heat_state',0);
INSERT into settings (option,value) VALUES ('ac_state',0);
INSERT into settings (option,value) VALUES ('servo_pos',10);
INSERT into settings (option,value) VALUES ('switches',999);