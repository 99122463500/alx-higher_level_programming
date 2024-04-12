#!/usr/bin/python3
"""
102-relationship_cities_states_list.py - list City objects
"""

from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from relationship_state import Base, State
from relationship_city import City
from sys import argv

if __name__ == "__main__":
    engine = create_engine("mysql+mysqldb://{}:{}@localhost/{}".format(
        argv[1], argv[2], argv[3]))

    Base.metadata.create_all(engine)
    Session = sessionmaker(bind=engine)
    session = Session()

    rows = session.query(City).order_by(City.id).all()
    for c in rows:
        print("{}: {} -> {}".format(c.id, c.name, c.state.name))

    session.close()
