function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33147, y = 32864, z = 07})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 33147, y = 32864, z = 07}, 15)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33147, y = 32864, z = 07})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 33147, y = 32864, z = 07}, 15)
end
