function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33205, y = 33002, z = 14})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33205, y = 33002, z = 14}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33205, y = 33002, z = 14})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33205, y = 33002, z = 14}, 11)
end
