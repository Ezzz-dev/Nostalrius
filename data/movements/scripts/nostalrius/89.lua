function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33254, y = 32704, z = 13})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33254, y = 32704, z = 13}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33254, y = 32704, z = 13})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33254, y = 32704, z = 13}, 11)
end
