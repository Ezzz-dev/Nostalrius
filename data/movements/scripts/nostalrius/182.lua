function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32201, y = 31845, z = 07})
	Game.sendMagicEffect({x = 32173, y = 31929, z = 07}, 11)
	creature:getPlayer():setStorageValue(Obj2,205,1)
end
